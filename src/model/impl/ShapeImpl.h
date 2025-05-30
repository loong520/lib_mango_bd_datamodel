//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class GraphElementImpl;

class ShapeImpl : public GObjectImpl {
public:
    static ShapeImpl *New(GraphElementImpl *parent);

    ShapeImpl(Object* parent = nullptr) : GObjectImpl(parent)
    {
    }
    ShapeImpl(const ShapeImpl &other);
    ShapeImpl* clone() const override;

    ObjectType getObjectType() const override { return ObjectType::kShape; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    void addSubShape(GObjectImpl *shape);
    void removeSubShape(GObjectImpl *shape);
    QList<GObjectImpl *> getSubShapes() const;

    bool isEmpty() const;

public:
    QList<GObjectImpl*> m_subShapes;
};

}
}
}
