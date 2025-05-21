//
// Created by 18224 on 2025/5/21.
//

#pragma once

#include "MangoBDDataModel/common/RTree.h"
#include "MangoBDDataModel/model/GObject.h"

#include <set>
#include <vector>

namespace mango {
namespace blockdiagram {
namespace datamodel {

class BDRTree
{
private:
    using RTree3D = RTree<GObject*, double, 3, double>;

public:
    BDRTree()
    {
        m_tree = new RTree3D();
        m_count = 0;
    }

    ~BDRTree()
    {
        delete this->m_tree;
    }

    /// 插入一个图元到树中
    /// \param aObject 图元指针
    void insert(GObject *aObject)
    {
        QRectF rect = aObject->getBoundingRect();

        // 为了安全、选中阴影等因素，稍微放大一点
        auto borderWidth = aObject->getBorderWidth();
        rect.adjust(-borderWidth, -borderWidth, borderWidth, borderWidth);

        const double type = quint16(aObject->getObjectType());
        const double mmin[3] = {type, rect.x(), rect.y()};
        const double mmax[3] = {type, rect.bottomRight().x(), rect.bottomRight().y()};

        m_tree->insert(mmin, mmax, aObject);
        m_count++;
    }

    /// 从树中删除一个图元
    /// \param aObject 图元指针
    /// \return 是否删除成功
    /// \note 删除操作通过比较指针来完成，尝试删除该项的副本将会失败。
    bool remove(GObject *aObject)
    {
        // 首先，尝试使用给定的边界框移除该项目
        QRectF rect = aObject->getBoundingRect();

        // 为了安全、选中阴影等因素，稍微放大一点
        auto borderWidth = aObject->getBorderWidth();
        rect.adjust(-borderWidth, -borderWidth, borderWidth, borderWidth);

        const double type = quint16(aObject->getObjectType());
        const double mmin[3] = {type, rect.x(), rect.y()};
        const double mmax[3] = {type, rect.bottomRight().x(), rect.bottomRight().y()};

        // 如果我们没有成功（true == 未找到），则将搜索范围扩大到整个树
        if (m_tree->remove(mmin, mmax, aObject)) {
            // 注意: 我们必须在整个树中搜索要移除的指针. 因为在我们有机会从树中删除该项之前，它可能已经被移动了
            const double mmin2[3] = {INT_MIN, INT_MIN, INT_MIN};
            const double mmax2[3] = {INT_MAX, INT_MAX, INT_MAX};
            if (m_tree->remove(mmin2, mmax2, aObject)) {
                return false;
            }
        }
        m_count--;
        return true;
    }

    /// 清空树中的所有图元
    void clear()
    {
        m_tree->removeAll();
        m_count = 0;
    }

    /// 确定给定的项是否存在于树中
    /// \param aObject 可能存在于树中的项
    /// \param aRobust 如果为true，则搜索整个树，而不仅仅是边界框
    /// \return 如果项确实存在，则为true，如果不存在，则为false
    /// \note 此操作不会搜索整个树，因此如果项已移动，则可能会返回false，即使它应该为true。
    bool contains(const GObject *aObject, bool aRobust = false) const
    {
        QRectF rect = aObject->getBoundingRect();

        // 为了安全、选中阴影等因素，稍微放大一点
        auto borderWidth = aObject->getBorderWidth();
        rect.adjust(-borderWidth, -borderWidth, borderWidth, borderWidth);

        const double type = quint16(aObject->getObjectType());
        const double mmin[3] = {type, rect.x(), rect.y()};
        const double mmax[3] = {type, rect.bottomRight().x(), rect.bottomRight().y()};
        bool found = false;

        auto search = [&found, &aObject](const GObject *aSearchItem) {
            if (aSearchItem == aObject) {
                found = true;
                return false;
            }
            return true;
        };
        m_tree->search(mmin, mmax, search);
        if (!found && aRobust) {
            // N.B. We must search the whole tree for the pointer to remove
            // because the item may have been moved.  We do not expand the item
            // type search as this should not change.

            const double mmin2[3] = {type, INT_MIN, INT_MIN};
            const double mmax2[3] = {type, INT_MAX, INT_MAX};

            m_tree->search(mmin2, mmax2, search);
        }
        return found;
    }

    /// 返回树中的图元数量
    /// \return 图元数量
    quint32 size() const
    {
        return m_count;
    }

    /// 返回树是否为空
    /// \return 是否为空
    bool empty() const
    {
        return m_count == 0;
    }

    using iterator = typename RTree3D::Iterator;

    /**
     * 为RTree提供一个类型特定的自动范围迭代器。使用此结构可以编写如下代码：
     *
     * for(auto item : rtree.ofType(kGObject))
     *
     * 仅迭代RTree中类型相同的项
     */
    struct IteratorByType
    {
        IteratorByType(RTree3D *aTree, ObjectType aType) : m_typeTree(aTree)
        {
            if (aType == ObjectType::kUnknown) {
                m_rect = {{INT_MIN, INT_MIN, INT_MIN}, {INT_MAX, INT_MAX, INT_MAX}};
            } else {
                const double type = quint16(aType);
                m_rect = {{type, INT_MIN, INT_MIN}, {type, INT_MAX, INT_MAX}};
            }
        };

        IteratorByType(RTree3D *aTree, ObjectType aType, const QRectF &aRect) : m_typeTree(aTree)
        {
            if (aType == ObjectType::kUnknown) {
                m_rect = {{INT_MIN, aRect.x(), aRect.y()},
                          {INT_MAX, aRect.bottomRight().x(), aRect.bottomRight().y()}};
            } else {
                const double type = quint16(aType);
                m_rect = {{type, aRect.x(), aRect.y()},
                          {type, aRect.bottomRight().x(), aRect.bottomRight().y()}};
            }
        };

        RTree3D::Rect m_rect;
        RTree3D*      m_typeTree;

        iterator begin()
        {
            return m_typeTree->begin(m_rect);
        }

        iterator end()
        {
            return m_typeTree->end(m_rect);
        }

        bool empty()
        {
            return m_typeTree->count() == 0;
        }
    };

    IteratorByType ofType(ObjectType aType) const
    {
        return IteratorByType(m_tree, aType);
    }

    IteratorByType overlapping(const QPointF &aPoint, int aAccuracy = 0) const
    {
        QRectF rect(aPoint, QPointF(0, 0));
        rect.adjust(-aAccuracy, -aAccuracy, aAccuracy, aAccuracy);
        return IteratorByType(m_tree, ObjectType::kUnknown, rect);
    }

    IteratorByType overlapping(ObjectType aType, const QPointF &aPoint, int aAccuracy = 0) const
    {
        QRectF rect(aPoint, QPointF(0, 0));
        rect.adjust(-aAccuracy, -aAccuracy, aAccuracy, aAccuracy);
        return IteratorByType(m_tree, aType, rect);
    }

    IteratorByType overlapping(const QRectF& aRect) const
    {
        return IteratorByType(m_tree, ObjectType::kUnknown, aRect);
    }

    IteratorByType overlapping(ObjectType aType, const QRectF &aRect) const
    {
        return IteratorByType(m_tree, aType, aRect);
    }

    /// 返回一个可读/写迭代器，该迭代器指向 #RTree3D 树中第一个元素
    /// \note 迭代顺序不是很明显，并且在您添加或移动项目并重新平衡 #RTree 时可能会发生变化。
    /// 任何向用户公开 #RTree 内容的操作都必须在呈现之前进行排序。
    iterator begin()
    {
        return m_tree->begin();
    }

    // 返回一个可读/写迭代器，该迭代器指向 #RTree3D 树中最后一个元素的下一个位置
    iterator end()
    {
        return m_tree->end();
    }

    const iterator begin() const
    {
        return m_tree->begin();
    }

    const iterator end() const
    {
        return m_tree->end();
    }

private:
    RTree3D* m_tree;
    quint32  m_count;
};

}
}
}