//
// Created by 18224 on 2025/5/7.
//

#include "GObjectImpl.h"

using namespace mango::blockdiagram::datamodel;

GObjectImpl::GObjectImpl(const GObjectImpl &other) : ObjectImpl(other)
{
    m_flags = other.m_flags;
    m_zValue = other.m_zValue;
    m_pos = other.m_pos;
    m_transform = other.m_transform;
    m_sceneTransform = other.m_sceneTransform;
    m_sceneTransformDirty = other.m_sceneTransformDirty;
}

GObjectImpl* GObjectImpl::clone() const
{
    return new GObjectImpl(*this);
}

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
    if (offset.isNull()) {
        return;
    }
    m_transform.translate(offset.x(), offset.y());
}

void GObjectImpl::setScale(double scale)
{
    m_transform.scale(scale, scale);
}

double GObjectImpl::getScale() const
{
    return m_transform.m11();
}

void GObjectImpl::setRotation(int angle)
{
    m_transform.rotate(angle);
}

void GObjectImpl::setRotation(QPointF center, int angle)
{
    // 将变换复合为：平移到中心 -> 旋转 -> 平移回来
    QTransform t;
    t.translate(center.x(), center.y());
    t.rotate(angle);
    t.translate(-center.x(), -center.y());
    m_transform *= t;
}

int GObjectImpl::getRotation() const
{
    return 0;
    // TODO: implement
}

void GObjectImpl::mirrorX()
{
    m_transform.scale(-1, 1);
}

 void GObjectImpl::mirrorY()
{
    m_transform.scale(1, -1);
}

void GObjectImpl::setTransform(const QTransform& transform)
{
    m_transform = transform;
}

QTransform GObjectImpl::getTransform() const
{
    return m_transform;
}

void GObjectImpl::concat(const QTransform& other)
{
    m_transform = other * m_transform;
}

int GObjectImpl::getZValue() const
{
    return m_zValue;
}

void GObjectImpl::setZValue(int zValue)
{
    m_zValue = zValue;
}

bool GObjectImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool GObjectImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

int GObjectImpl::getBorderWidth() const
{
    return 1;
}

void GObjectImpl::setBorderWidth(int width)
{
    // todo: implement
}

void GObjectImpl::inflateAndTransform(QRectF &rect) const
{
    if (auto bw = getBorderWidth() / 2.0; (!qFuzzyIsNull(bw) && (bw > 0.0))) {
        rect.adjust(-bw, -bw, bw, bw);
    }
    rect = m_transform.mapRect(rect);
}