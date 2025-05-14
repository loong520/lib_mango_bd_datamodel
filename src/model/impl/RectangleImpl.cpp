//
// Created by 18224 on 2025/5/7.
//

#include "RectangleImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

Rectangle* RectangleImpl::New(Shape* parent)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    RectangleImpl* impl = new RectangleImpl((Object*)parent);

    obj_impl_ptr(Shape, parent)->addSubShape((GObjectImpl*)impl);

    return (Rectangle*)impl;
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

void RectangleImpl::setTopLeft(const QPointF& topLeft)
{
    m_topLeft = topLeft;
}

QPointF RectangleImpl::getTopLeft() const
{
    return m_topLeft;
}

void RectangleImpl::setWidth(double width)
{
    m_width = width;
}

double RectangleImpl::getWidth() const
{
    return m_width;
}

void RectangleImpl::setHeight(double height)
{
    m_height = height;
}

void RectangleImpl::setSize(const QSize& size)
{
    m_width = size.width();
    m_height = size.height();
}

double RectangleImpl::getHeight() const
{
    return m_height;
}

QSize RectangleImpl::getSize() const
{
    return QSize(m_width, m_height);
}