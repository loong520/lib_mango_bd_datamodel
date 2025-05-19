//
// Created by 18224 on 2025/5/7.
//

#include "ObjectImpl.h"
#include "PropertyImpl.h"
#include "MangoBDDataModel/base/PropertyDef.h"

using namespace mango::blockdiagram::datamodel;

ObjectImpl::ObjectImpl(Object *parent)
    : m_parent(parent), m_props(nullptr)
{
    // todo: ObjectStore::getInstance().addObject((Object*)this);
}

ObjectImpl::~ObjectImpl()
{
    if (m_props) {
        auto it = this->m_props->begin();
        while (it != m_props->end()) {
            delete (PropertyImpl *)(it.value());
            ++it;
        }
    }
    delete m_props;

    // todo: ObjectStore::getInstance().removeObject((Object*)this);
}

bool ObjectImpl::isTypeOf(const ObjectType &type) const
{
    return (type.getType() == ObjectType::kObject);
}

void ObjectImpl::Delete()
{
}

DBID ObjectImpl::getDbid() const
{
    return (DBID)this;
}

bool ObjectImpl::isAlive()
{
    // todo: return ObjectStore::getInstance().hasObject((Object*)this);
    return false;
}

Object *ObjectImpl::getParent() const
{
    return m_parent;
}

void ObjectImpl::setParent(Object *parent)
{
    m_parent = parent;
}

bool ObjectImpl::hasProperty() const
{
    return m_props && !m_props->isEmpty();
}

void ObjectImpl::addProperty(Property *property)
{
    if (property == nullptr ||
        property->getOwner() != (Object*)this ||
        property->getValueString().isEmpty()) {
        return;
    }
    // 检查属性是否重复添加
    Property* oldProp = findProperty(property->getName());
    if (oldProp == property) {
        return;
    }

    // 增加该属性的使用计数
    PropertyDef* def = property->getPropertyDef();
    if (def) {
        def->incUseCount(1);
    }
    if (m_props == nullptr) {
        m_props = new QMap<QString, Property*>();
    }
    m_props->insert(property->getName(), property);
}

void ObjectImpl::deleteProperty(const QString& name)
{
    if (m_props == nullptr) {
        return;
    }

    auto it = m_props->find(name);
    if (it != m_props->end()) {
        PropertyImpl* impl = (PropertyImpl*)it.value();

        PropertyDef* def = impl->getPropertyDef();
        if (def) {
            def->incUseCount(-1);
        }

        delete impl;
        m_props->erase(it);
    }
}

Property *ObjectImpl::findProperty(const QString &name) const
{
    if (m_props == nullptr) {
        return nullptr;
    }
    return m_props->value(name, nullptr);
}

QList<Property *> ObjectImpl::getProperties() const
{
    if (m_props == nullptr) {
        return QList<Property *>();
    }
    return m_props->values();
}
