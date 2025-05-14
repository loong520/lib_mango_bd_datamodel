//
// Created by 18224 on 2025/5/7.
//

#include "ShapeImpl.h"
#include "GraphElementImpl.h"
#include "Rectangle.h"

using namespace mango::blockdiagram::datamodel;

Shape *ShapeImpl::New(GraphElement *parent)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    ShapeImpl* impl = new ShapeImpl((Object*)parent);
    obj_impl_ptr(GraphElement, parent)->setShape(impl);

    return (Shape*)impl;
}

bool ShapeImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kShape) {
        return true;
    }
    return false;
}

void ShapeImpl::Delete()
{
    if (!m_parent) {
        // TODO: LOG_ERROR
        return;
    }
    ObjectType::TypeId typeId = m_parent->getObjectType();
    if (typeId == ObjectType::kShape) {
        obj_impl_ptr(Shape, m_parent)->removeSubShape((GObjectImpl*)this);
    }
}

void ShapeImpl::addSubShape(GObjectImpl *shape)
{
    if (!shape) {
        return;
    }
    if (m_subShapes.contains(shape)) {
        return;
    }
    m_subShapes.append(shape);
    shape->setParent((Object*)this);
}

void ShapeImpl::removeSubShape(GObjectImpl *shape)
{
    if (!shape) {
        return;
    }
    m_subShapes.removeAll(shape);
    delete shape;
}

QList<GObjectImpl *> ShapeImpl::getSubShapes() const
{
    return m_subShapes;
}

bool ShapeImpl::isEmpty() const
{
    return m_subShapes.isEmpty();
}