//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Arc;
class Shape;

class ArcImpl : public GObjectImpl {
public:
    static Arc* New(Shape* parent);

    ArcImpl(Object* parent = nullptr) : GObjectImpl(parent)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kArc; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
};

}
}
}