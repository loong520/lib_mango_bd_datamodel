//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GObject.h"
#include <QPolygonF>

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Shape;

class MANGO_BD_DATAMODEL_API Polygon : public GObject {
public:
    /// 创建一个新的多边形对象
    /// \param parent 父对象
    /// \return
    static Polygon* New(Shape* parent);
    static Polygon* New(Shape* parent, const QList<QPointF> &v);

    /// 转换为QPolygonF
    /// \return QPolygonF对象
    QPolygonF toQPolygon() const;

    /// 点数量
    /// \return 点数量
    int size() const;

    /// 是否为空
    /// \return 是否为空
    bool isEmpty() const;

    /// 获取第一个点
    /// \return 第一个点
    QPointF& first();

    /// 获取第一个点
    /// \return 第一个点
    const QPointF& constFirst() const;

    /// 获取最后一个点
    /// \return 最后一个点
    QPointF& last();

    /// 获取最后一个点
    /// \return 最后一个点
    const QPointF& constLast() const;

    /// 获取第i个点
    /// \param i 点索引
    /// \return 第i个点
    const QPointF& get(int i) const;

    /// 添加点
    /// \param p 点坐标
    void append(const QPointF &p);

    /// 添加多个点
    /// \param points 点坐标列表
    void append(const QList<QPointF> &points);

    /// 在第一个点前添加点
    /// \param p 点坐标
    void prepend(const QPointF &p);

    /// 替换指定点坐标
    /// \param index 点索引
    /// \param p 点坐标
    void replace(int index, const QPointF &p);

    /// 删除指定点
    /// \param i 点索引
    void removeAt(int i);

    /// 删除第一个点
    void removeFirst();

    /// 删除最后一个点
    void removeLast();

    /// 清空所有点
    void clear();
};

}
}
}
