//
// Created by 18224 on 2025/5/7.
//

#include "include/model/GObject.h"
#include "impl/GObjectImpl.h"

using namespace mango::blockdiagram::datamodel;

int GObject::getFlags() const
{
    return impl_ptr(GObject)->getFlags();
}

void GObject::setFlags(int flags)
{
    impl_ptr(GObject)->setFlags(flags);
}

bool GObject::isSelected() const
{
    return impl_ptr(GObject)->isSelected();
}

bool GObject::isMoving() const
{
    return impl_ptr(GObject)->isMoving();
}

bool GObject::isModified() const
{
    return impl_ptr(GObject)->isModified();
}

bool GObject::isVisible() const
{
    return impl_ptr(GObject)->isVisible();
}

bool GObject::isFixed() const
{
    return impl_ptr(GObject)->isFixed();
}

void GObject::setSelected(bool selected)
{
    impl_ptr(GObject)->setSelected(selected);
}

void GObject::setMoving(bool moving)
{
    impl_ptr(GObject)->setMoving(moving);
}

void GObject::setModified(bool modified)
{
    impl_ptr(GObject)->setModified(modified);
}

void GObject::setVisible(bool visible)
{
    impl_ptr(GObject)->setVisible(visible);
}

void GObject::setFixed(bool fixed)
{
    impl_ptr(GObject)->setFixed(fixed);
}