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

class PolygonImpl : public GObjectImpl {
public:
    static Polygon* New(Shape* parent);

    PolygonImpl(Object* parent = nullptr) : GObjectImpl(parent)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kPolygon; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

public:
    QList<QPointF> m_points;
};

}
}
}