//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Polyline;
class Shape;

class PolylineImpl : public GObjectImpl {
public:
    static Polyline* New(Shape* parent);

    PolylineImpl(Object* parent = nullptr) : GObjectImpl(parent)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kPolyline; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;

public:
    QList<QPointF> m_points;
};

}
}
}