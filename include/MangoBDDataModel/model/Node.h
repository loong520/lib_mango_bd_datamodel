//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GraphElement.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Pin;
class Net;

class MANGO_BD_DATAMODEL_API Node : public GraphElement {
public:
    /// 创建一个新的节点对象
    /// \param parent 父节点
    /// \return 新建节点对象
    /// \note parent为空视为root节点，不会有shape
    static Node* New(Node* parent);

    /// 初始化节点大小
    /// \note root节点调用该函数无效
    void initNodeSize();

    /// 节点大小
    /// \return 大小
    QSize getSize() const;

    /// 是否为根节点
    /// \return 是否为根节点
    bool isRootNode() const;

    /// 是否为层次节点
    /// \return 是否为层次节点
    bool isHierarchical() const;

    /// 增加子图元
    /// \param graphElement 子图元
    void addGraphElement(GraphElement *graphElement);

    /// 删除子图元
    /// \param graphElement 子图元
    void removeGraphElement(GraphElement *graphElement);

    /// 获取子图元
    QList<GraphElement*> getGraphElements() const;

    /// 获取子图元
    /// \param type 子图元类型
    /// \return 子图元列表
    QList<GraphElement*> getGraphElements(ObjectType type) const;

    /// 增加子节点
    /// \param node 子节点
    void addSubNode(Node *node);

    /// 删除子节点
    /// \param node 子节点
    void removeSubNode(Node *node);

    /// 获取子节点
    /// \return 子节点列表
    QList<Node*> getSubNodes() const;

    /// 增加内部引脚
    /// \param pin 内部引脚
    void addInternalPin(Pin *pin);

    /// 删除内部引脚
    /// \param pin 内部引脚
    void removeInternalPin(Pin *pin);

    /// 获取内部引脚
    /// \return 内部引脚列表
    QList<Pin*> getInternalPins() const;

    /// 增加边界引脚
    /// \param pin 边界引脚
    void addBoundaryPin(Pin *pin);

    /// 删除边界引脚
    /// \param pin 边界引脚
    void removeBoundaryPin(Pin *pin);

    /// 获取边界引脚
    /// \return 边界引脚列表
    QList<Pin*> getBoundaryPins() const;

    /// 增加网络
    /// \param net 网络
    void addNet(Net *net);

    /// 删除网络
    /// \param net 网络
    void removeNet(Net *net);

    /// 获取网络
    /// \return 网络列表
    QList<Net*> getNets() const;


//    QList<GObject *> items(const QPointF &pos, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder) const;
//    QList<GObject *> items(const QRectF &rect, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder) const;
//    QList<GObject *> items(const QPainterPath &path, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder) const;

};

}
}
}