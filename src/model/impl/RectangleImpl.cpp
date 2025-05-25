//
// Created by 18224 on 2025/5/7.
//

#include "RectangleImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

RectangleImpl* RectangleImpl::New(ShapeImpl* parent)
{
    return New(parent, {});
}

RectangleImpl* RectangleImpl::New(ShapeImpl* parent, const QRectF &rect)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    RectangleImpl* impl = new RectangleImpl(rect, (Object*)parent);
    parent->addSubShape((GObjectImpl*)impl);

    return impl;
}

RectangleImpl::RectangleImpl(const RectangleImpl& other) : GObjectImpl(other)
{
    m_rect = other.m_rect;
}

RectangleImpl* RectangleImpl::clone() const
{
    return new RectangleImpl(*this);
}

bool RectangleImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kRectangle) {
        return true;
    }
    return false;
}

void RectangleImpl::Delete()
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

QRectF RectangleImpl::getBoundingRect() const
{
    QRectF rect = m_rect;

    inflateAndTransform(rect);

    return rect;
}

bool RectangleImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool RectangleImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

void RectangleImpl::setRect(const QRectF &rect)
{
    m_rect = rect;
}

void RectangleImpl::setTopLeft(const QPointF& topLeft)
{
    m_rect.setTopLeft(topLeft);
}

void RectangleImpl::setWidth(double width)
{
    m_rect.setWidth(width);
}

void RectangleImpl::setHeight(double height)
{
    m_rect.setHeight(height);
}

void RectangleImpl::setSize(const QSizeF& size)
{
    m_rect.setSize(size);
}