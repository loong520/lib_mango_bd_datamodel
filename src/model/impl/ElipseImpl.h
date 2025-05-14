//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Elipse;
class Shape;

class ElipseImpl : public GObjectImpl {
public:
    static Elipse* New(Shape* parent);

    ElipseImpl(Object* parent = nullptr) : GObjectImpl(parent)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kElipse; }
    bool isTypeOf(const ObjectType &type) const override;
    void Delete() override;
};

}
}
}