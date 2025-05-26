//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/base/Property.h"
#include "impl/PropertyImpl.h"

using namespace mango::blockdiagram::datamodel;

Property* Property::New(Object* owner, const QString& name, bool value)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, value);
}

Property* Property::New(Object* owner, const QString& name, int value)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, value);
}

Property* Property::New(Object* owner, const QString& name, double value)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, value);
}

Property* Property::New(Object* owner, const QString& name, const char * value)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, value);
}

Property* Property::New(Object* owner, const QString& name, const std::string &str)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, str);
}

Property* Property::New(Object* owner, const QString& name, const QString& value)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, value);
}

Property* Property::New(Object* owner, const QString& name, const QVector<bool> &vb)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, vb);
}

Property* Property::New(Object* owner, const QString& name, const QVector<int> &vi)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, vi);
}

Property* Property::New(Object* owner, const QString& name, const QVector<double> &vd)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, vd);
}

Property* Property::New(Object* owner, const QString& name, const QList<QString>& ls)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, ls);
}

Property* Property::New(Object* owner, const QString& name, std::initializer_list<bool> il)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, il);
}

Property* Property::New(Object* owner, const QString& name, std::initializer_list<int> il)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, il);
}

Property* Property::New(Object* owner, const QString& name, std::initializer_list<double> il)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, il);
}

Property* Property::New(Object* owner, const QString& name, std::initializer_list<const char *> il)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, il);
}

Property* Property::New(Object* owner, const QString& name, Object* value)
{
    return (Property*)PropertyImpl::New((ObjectImpl*)owner, name, value);
}

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

std::optional<Object*> Property::asObject() const
{
    std::optional<ObjectImpl*> opt_impl = impl_ptr(Property)->asObject();

    if (opt_impl.has_value()) {
        return std::optional<Object*>{(Object*)(opt_impl.value())};
    } else {
        return std::nullopt;
    }
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
    return (Object*)impl_ptr(Property)->getOwner();
}

QString Property::getValueString() const
{
    return impl_ptr(Property)->getValueString();
}

QString Property::printInfo() const
{
    return impl_ptr(Property)->printInfo();
}