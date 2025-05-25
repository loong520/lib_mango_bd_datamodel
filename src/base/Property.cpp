//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/base/Property.h"
#include "impl/PropertyImpl.h"

using namespace mango::blockdiagram::datamodel;

std::optional<bool> Property::asBool() const
{
    return impl_ptr(Property)->asBool();
}

std::optional<int> Property::asInt() const
{
    return impl_ptr(Property)->asInt();
}

std::optional<double> Property::asReal() const
{
    return impl_ptr(Property)->asReal();
}

std::optional<QString> Property::asString() const
{
    return impl_ptr(Property)->asString();
}

std::optional<QVector<bool>> Property::asBoolArray() const
{
    return impl_ptr(Property)->asBoolArray();
}

std::optional<QVector<int>> Property::asIntArray() const
{
    return impl_ptr(Property)->asIntArray();
}

std::optional<QVector<double>> Property::asDoubleArray() const
{
    return impl_ptr(Property)->asDoubleArray();
}

std::optional<QList<QString>> Property::asStringArray() const
{
    return impl_ptr(Property)->asStringArray();
}

QString Property::getName() const
{
    return impl_ptr(Property)->getName();
}

Object* Property::getOwner() const
{
    return impl_ptr(Property)->getOwner();
}

QString Property::getValueString() const
{
    return impl_ptr(Property)->getValueString();
}