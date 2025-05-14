//
// Created by 18224 on 2025/5/7.
//

#include "GObjectImpl.h"
#include "GObject.h"

using namespace mango::blockdiagram::datamodel;

bool GObjectImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject) {
        return true;
    }
    return false;
}

void GObjectImpl::Delete()
{
}

QRectF GObjectImpl::getBoundingRect() const
{
    return QRectF();
}

quint32 GObjectImpl::getFlags() const
{
    return m_flags;
}

void GObjectImpl::setFlags(quint32 flags)
{
    m_flags = flags;
}

bool GObjectImpl::hasFlag(quint32 flag) const
{
    return (m_flags & flag) == flag;
}

void GObjectImpl::setFlag(quint32 flag, bool on)
{
    if (on) {
        m_flags |= flag;
    } else {
        m_flags &= ~flag;
    }
}

bool GObjectImpl::isSelected() const
{
    return m_flags & ObjectIsSelected;
}

bool GObjectImpl::isMoving() const
{
    return m_flags & ObjectIsMoving;
}

bool GObjectImpl::isModified() const
{
    return m_flags & ObjectIsModified;
}

bool GObjectImpl::isVisible() const
{
    return m_flags & ObjectIsVisible;
}

bool GObjectImpl::isFixed() const
{
    return m_flags & ObjectIsFixed;
}

void GObjectImpl::setSelected(bool selected)
{
    if (selected) {
        m_flags |= ObjectIsSelected;
    } else {
        m_flags &= ~ObjectIsSelected;
    }
}

void GObjectImpl::setMoving(bool moving)
{
    if (moving) {
        m_flags |= ObjectIsMoving;
    } else {
        m_flags &= ~ObjectIsMoving;
    }
}

void GObjectImpl::setModified(bool modified)
{
    if (modified) {
        m_flags |= ObjectIsModified;
    } else {
        m_flags &= ~ObjectIsModified;
    }
}

void GObjectImpl::setVisible(bool visible)
{
    if (visible) {
        m_flags |= ObjectIsVisible;
    } else {
        m_flags &= ~ObjectIsVisible;
    }
}

void GObjectImpl::setFixed(bool fixed)
{
    if (fixed) {
        m_flags |= ObjectIsFixed;
    } else {
        m_flags &= ~ObjectIsFixed;
    }
}

void GObjectImpl::setPos(const QPointF& pos)
{
    m_pos = pos;
}

QPointF GObjectImpl::getPos() const
{
    return m_pos;
}

void GObjectImpl::translate(const QPointF& offset)
{
    m_pos += offset;
}

void GObjectImpl::setRotation(int angle)
{
    m_rotation = angle;
}

void GObjectImpl::setRotation(QPointF center, int angle)
{
    // TODO: implement
}

int GObjectImpl::getRotation() const
{
    return m_rotation;
}

void GObjectImpl::mirrorX()
{
    // TODO: implement
}

 void GObjectImpl::mirrorY()
{
    // TODO: implement
}

int GObjectImpl::getZValue() const
{
    return m_zValue;
}

void GObjectImpl::setZValue(int zValue)
{
    m_zValue = zValue;
}