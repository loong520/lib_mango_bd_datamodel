//
// Created by 18224 on 2025/5/7.
//

#include "Object.h"
#include "impl/ObjectImpl.h"

using namespace mango::blockdiagram;
using namespace mango::blockdiagram::datamodel;

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

void Object::destory()
{
    // 先调用实现类的destory方法, 移除关联信息
    impl_ptr(Object)->destory();

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
    impl_ptr(Object)->addProperty(property);
}

void Object::deleteProperty(const QString& name)
{
    impl_ptr(Object)->deleteProperty(name);
}

Property *Object::findProperty(const QString &name) const
{
    return impl_ptr(Object)->findProperty(name);
}

QList<Property *> Object::getProperties() const
{
    return impl_ptr(Object)->getProperties();
}
