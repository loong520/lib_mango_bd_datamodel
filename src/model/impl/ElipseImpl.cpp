//
// Created by 18224 on 2025/5/7.
//

#include "ElipseImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

Elipse* ElipseImpl::New(Shape* parent)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    ElipseImpl* impl = new ElipseImpl((Object*)parent);

    obj_impl_ptr(Shape, parent)->addSubShape((GObjectImpl*)impl);

    return (Elipse*)impl;
}

bool ElipseImpl::isTypeOf(const ObjectType &type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kElipse) {
        return true;
    }
    return false;
}

void ElipseImpl::Delete()
{
    if (!m_parent) {
        // TODO: LOG_ERROR
        return;
    }

    ObjectType::TypeId typeId = m_parent->getObjectType();
    if (typeId == ObjectType::kShape) {
        obj_impl_ptr(Shape, m_parent)->removeSubShape((GObjectImpl*)this);
    } else {
        // TODO: LOG_ERROR
        return;
    }
}