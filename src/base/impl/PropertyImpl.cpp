//
// Created by 18224 on 2025/5/7.
//

#include "PropertyImpl.h"

using namespace mango::blockdiagram::datamodel;

QString PropertyImpl::getName() const
{
    return QString();
}

PropertyDef* PropertyImpl::getPropertyDef() const
{
    return nullptr;
}

Object* PropertyImpl::getOwner() const
{
    return nullptr;
}

QString PropertyImpl::getValueString() const
{
    return QString();
}