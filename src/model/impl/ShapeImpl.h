//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Shape;
class GraphElement;

class ShapeImpl : public GObjectImpl {
public:
    static Shape *New(GraphElement *parent);

    ShapeImpl(Object* parent = nullptr) : GObjectImpl(parent)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kShape; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;

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
