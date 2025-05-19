//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/GObject.h"
#include "impl/GObjectImpl.h"

using namespace mango::blockdiagram::datamodel;

quint32 GObject::getFlags() const
{
    return impl_ptr(GObject)->getFlags();
}

void GObject::setFlags(quint32 flags)
{
    impl_ptr(GObject)->setFlags(flags);
}

bool GObject::hasFlag(quint32 flag) const
{
    return (impl_ptr(GObject)->hasFlag(flag));
}

void GObject::setFlag(quint32 flag, bool on)
{
    impl_ptr(GObject)->setFlag(flag, on);
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

QRectF GObject::getBoundingRect() const
{
    return impl_ptr(GObject)->getBoundingRect();
}

QPointF GObject::getPos() const
{
    return impl_ptr(GObject)->getPos();
}

void GObject::setPos(const QPointF& pos)
{
    impl_ptr(GObject)->setPos(pos);
}

void GObject::translate(const QPointF& offset)
{
    impl_ptr(GObject)->translate(offset);
}

void GObject::translate(double dx, double dy)
{
    impl_ptr(GObject)->translate({dx, dy});
}

void GObject::setScale(double scale)
{
    impl_ptr(GObject)->setScale(scale);
}

double GObject::getScale() const
{
    return impl_ptr(GObject)->getScale();
}

int GObject::getRotation() const
{
    return impl_ptr(GObject)->getRotation();
}

void GObject::setRotation(int angle)
{
    impl_ptr(GObject)->setRotation(angle);
}

void GObject::setRotation(QPointF center, int angle)
{
    impl_ptr(GObject)->setRotation(center, angle);
}

void GObject::mirrorX()
{
    impl_ptr(GObject)->mirrorX();
}

void GObject::mirrorY()
{
    impl_ptr(GObject)->mirrorY();
}

void GObject::concat(const QTransform& other)
{
    impl_ptr(GObject)->concat(other);
}

QTransform GObject::getTransform() const
{
    return impl_ptr(GObject)->getTransform();
}

int GObject::getZValue() const
{
    return impl_ptr(GObject)->getZValue();
}

void GObject::setZValue(int zValue)
{
    impl_ptr(GObject)->setZValue(zValue);
}

bool GObject::hitTest(const QPointF& aPosition, int aAccuracy) const
{
    return impl_ptr(GObject)->hitTest(aPosition, aAccuracy);
}

bool GObject::hitTest(const QRectF& aRect, bool aContained, int aAccuracy) const
{
    return impl_ptr(GObject)->hitTest(aRect, aContained, aAccuracy);
}

int GObject::getBorderWidth() const
{
    return impl_ptr(GObject)->getBorderWidth();
}

void GObject::setBorderWidth(int width)
{
    impl_ptr(GObject)->setBorderWidth(width);
}