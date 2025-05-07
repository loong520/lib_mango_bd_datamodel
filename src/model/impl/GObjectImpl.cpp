//
// Created by 18224 on 2025/5/7.
//

#include "GObjectImpl.h"
#include "Defines.h"

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

void GObjectImpl::destory()
{
}

void GObjectImpl::setFlags(int flags)
{
    m_flags = flags;
}

int GObjectImpl::getFlags() const
{
    return m_flags;
}

bool GObjectImpl::isSelected() const
{
    return m_flags & GFLAG_SELECTED;
}

bool GObjectImpl::isMoving() const
{
    return m_flags & GFLAG_MOVING;
}

bool GObjectImpl::isModified() const
{
    return m_flags & GFLAG_CHANGED;
}

bool GObjectImpl::isVisible() const
{
    return m_flags & GFLAG_VISIBLE;
}

bool GObjectImpl::isFixed() const
{
    return m_flags & GFLAG_FIXED;
}

void GObjectImpl::setSelected(bool selected)
{
    if (selected) {
        m_flags |= GFLAG_SELECTED;
    } else {
        m_flags &= ~GFLAG_SELECTED;
    }
}

void GObjectImpl::setMoving(bool moving)
{
    if (moving) {
        m_flags |= GFLAG_MOVING;
    } else {
        m_flags &= ~GFLAG_MOVING;
    }
}

void GObjectImpl::setModified(bool modified)
{
    if (modified) {
        m_flags |= GFLAG_CHANGED;
    } else {
        m_flags &= ~GFLAG_CHANGED;
    }
}

void GObjectImpl::setVisible(bool visible)
{
    if (visible) {
        m_flags |= GFLAG_VISIBLE;
    } else {
        m_flags &= ~GFLAG_VISIBLE;
    }
}

void GObjectImpl::setFixed(bool fixed)
{
    if (fixed) {
        m_flags |= GFLAG_FIXED;
    } else {
        m_flags &= ~GFLAG_FIXED;
    }
}