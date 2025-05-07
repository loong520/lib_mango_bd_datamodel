//
// Created by 18224 on 2025/5/7.
//

#include "Property.h"
#include "impl/PropertyImpl.h"

using namespace mango::blockdiagram::datamodel;

QString Property::getName() const
{
    return impl_ptr(Property)->getName();
}

PropertyDef* Property::getPropertyDef() const
{
    return impl_ptr(Property)->getPropertyDef();
}

Object* Property::getOwner() const
{
    return impl_ptr(Property)->getOwner();
}

QString Property::getValueString() const
{
    return impl_ptr(Property)->getValueString();
}