//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/base/Object.h"
#include "impl/ObjectImpl.h"

using namespace mango::blockdiagram::datamodel;

Object *Object::clone() const
{
    return (Object*)impl_ptr(Object)->clone();
}

ObjectType Object::getObjectType() const
{
    return impl_ptr(Object)->getObjectType();
}

bool Object::isTypeOf(const ObjectType& type) const
{
    return impl_ptr(Object)->isTypeOf(type);
}

DBID Object::getDbid() const
{
    return impl_ptr(Object)->getDbid();
}

bool Object::isAlive()
{
    // todo: return ObjectStore::getInstance().hasObject(this);
    return false;
}

void Object::Delete()
{
    // 先调用实现类的Delete方法, 移除关联信息
    impl_ptr(Object)->Delete();

    // 再删除对象
    ObjectImpl* obj = (ObjectImpl*)this;
    delete obj;
}

Object *Object::getParent() const
{
    return impl_ptr(Object)->getParent();
}

bool Object::hasProperty() const
{
    return impl_ptr(Object)->hasProperty();
}

void Object::addProperty(Property *property)
{
    impl_ptr(Object)->addProperty((PropertyImpl*)property);
}

void Object::deleteProperty(const QString& name)
{
    impl_ptr(Object)->deleteProperty(name);
}

Property *Object::findProperty(const QString &name) const
{
    return (Property*)impl_ptr(Object)->findProperty(name);
}

QList<Property *> Object::getProperties() const
{
    auto &&properties = impl_ptr(Object)->getProperties();
    QList<Property*> retProperties;
    retProperties.reserve(properties.size());
    for (auto property : properties) {
        retProperties.append((Property*)property);
    }
    return retProperties;
}
