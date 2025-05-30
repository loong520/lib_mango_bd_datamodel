//
// Created by 18224 on 2025/5/7.
//

#include "ShapeImpl.h"
#include "GraphElementImpl.h"

using namespace mango::blockdiagram::datamodel;

ShapeImpl *ShapeImpl::New(GraphElementImpl *parent)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    ShapeImpl* impl = new ShapeImpl((Object*)parent);
    parent->setShape(impl);

    return impl;
}

ShapeImpl::ShapeImpl(const ShapeImpl &other) : GObjectImpl(other)
{
    if (other.m_subShapes.size() > 0) {
        m_subShapes.reserve(other.m_subShapes.size());

        for (auto subShape : other.m_subShapes) {
            GObjectImpl* newShape = subShape->clone();
            m_subShapes.append(newShape);
        }
    }
}

ShapeImpl* ShapeImpl::clone() const
{
    return new ShapeImpl(*this);
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


QRectF ShapeImpl::getBoundingRect() const
{
    QRectF bounds;
    for (auto shape : m_subShapes) {
        auto subRect = shape->getBoundingRect();
        subRect = m_transform.mapRect(subRect);
        bounds |= subRect;
    }
    return bounds;
}

bool ShapeImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool ShapeImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
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