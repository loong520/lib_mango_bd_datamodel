//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "Property.h"
#include "ObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class PropertyImpl : public ObjectImpl {
public:
    QString getName() const;

    PropertyDef* getPropertyDef() const;

    Object* getOwner() const;

    QString getValueString() const;
};

}
}
}