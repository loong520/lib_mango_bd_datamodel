//
// Created by 18224 on 2025/5/7.
//

#include "include/model/GObject.h"
#include "impl/GObjectImpl.h"

using namespace mango::blockdiagram::datamodel;

quint32 GObject::getFlags() const
{
    return impl_ptr(GObject)->m_flags;
}

void GObject::setFlags(quint32 flags)
{
    impl_ptr(GObject)->m_flags = flags;
}

bool GObject::hasFlag(quint32 flag) const
{
    return (impl_ptr(GObject)->m_flags & flag) == flag;
}

void GObject::setFlag(quint32 flag, bool on)
{
    if (on) {
        impl_ptr(GObject)->m_flags |= flag;
    } else {
        impl_ptr(GObject)->m_flags &= ~flag;
    }
}

bool GObject::isSelected() const
{
    return impl_ptr(GObject)->m_flags & ObjectIsSelected;
}

bool GObject::isMoving() const
{
    return impl_ptr(GObject)->m_flags & ObjectIsMoving;
}

bool GObject::isModified() const
{
    return impl_ptr(GObject)->m_flags & ObjectIsModified;
}

bool GObject::isVisible() const
{
    return impl_ptr(GObject)->m_flags & ObjectIsVisible;
}

bool GObject::isFixed() const
{
    return impl_ptr(GObject)->m_flags & ObjectIsFixed;
}

void GObject::setSelected(bool selected)
{
    if (selected) {
        impl_ptr(GObject)->m_flags |= ObjectIsSelected;
    } else {
        impl_ptr(GObject)->m_flags &= ~ObjectIsSelected;
    }
}

void GObject::setMoving(bool moving)
{
    if (moving) {
        impl_ptr(GObject)->m_flags |= ObjectIsMoving;
    } else {
        impl_ptr(GObject)->m_flags &= ~ObjectIsMoving;
    }
}

void GObject::setModified(bool modified)
{
    if (modified) {
        impl_ptr(GObject)->m_flags |= ObjectIsModified;
    } else {
        impl_ptr(GObject)->m_flags &= ~ObjectIsModified;
    }
}

void GObject::setVisible(bool visible)
{
    if (visible) {
        impl_ptr(GObject)->m_flags |= ObjectIsVisible;
    } else {
        impl_ptr(GObject)->m_flags &= ~ObjectIsVisible;
    }
}

void GObject::setFixed(bool fixed)
{
    if (fixed) {
        impl_ptr(GObject)->m_flags |= ObjectIsFixed;
    } else {
        impl_ptr(GObject)->m_flags &= ~ObjectIsFixed;
    }
}

QRectF GObject::getBoundingRect() const
{
    return impl_ptr(GObject)->getBoundingRect();
}

QPointF GObject::getPos() const
{
    return impl_ptr(GObject)->m_pos;
}

void GObject::setPos(const QPointF& pos)
{
    impl_ptr(GObject)->m_pos = pos;
}


int GObject::getRotation() const
{
    return impl_ptr(GObject)->m_rotation;
}

void GObject::setRotation(int angle)
{
    impl_ptr(GObject)->m_rotation = angle;
}

void GObject::translate(const QPointF& offset)
{
    impl_ptr(GObject)->m_pos += offset;
}

int GObject::getZValue() const
{
    return impl_ptr(GObject)->m_zValue;
}

void GObject::setZValue(int zValue)
{
    impl_ptr(GObject)->m_zValue = zValue;
}