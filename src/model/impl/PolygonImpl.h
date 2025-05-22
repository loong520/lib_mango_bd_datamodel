//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Polygon;
class Shape;

class PolygonImpl : public GObjectImpl, QList<QPointF> {
public:
    static Polygon* New(Shape* parent);
    static Polygon* New(Shape* parent, const QList<QPointF> &v);

    PolygonImpl(const QList<QPointF> &v, Object* parent = nullptr)
        : GObjectImpl(parent), QList<QPointF>(v)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kPolygon; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    int size() const { return QList<QPointF>::length(); }
    bool isEmpty() const { return QList<QPointF>::isEmpty(); }
    QPolygonF toQPolygon() const;

    // 获取点
    QPointF& first() { return QList<QPointF>::first(); }
    const QPointF& constFirst() const { return QList<QPointF>::constFirst(); }
    QPointF& last() { return QList<QPointF>::last(); }
    const QPointF& constLast() const { return QList<QPointF>::constLast(); }
    const QPointF& get(int i) const { return QList<QPointF>::at(i); }

    // 添加点
    void append(const QPointF &p);
    void append(const QList<QPointF> &points);
    void prepend(const QPointF &p);
    void replace(int index, const QPointF &p);

    // 删除点
    void removeAt(int i);
    void removeFirst();
    void removeLast();
    void clear();
};

}
}
}