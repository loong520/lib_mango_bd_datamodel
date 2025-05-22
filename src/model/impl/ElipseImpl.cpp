//
// Created by 18224 on 2025/5/7.
//

#include "EllipseImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

Ellipse* EllipseImpl::New(Shape* parent)
{
    return New(parent, 0.0, 0.0, {});
}

Ellipse* EllipseImpl::New(Shape* parent, double radiusX, double radiusY, const QPointF& center)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    EllipseImpl* impl = new EllipseImpl(radiusX, radiusY, center, (Object*)parent);
    obj_impl_ptr(Shape, parent)->addSubShape((GObjectImpl*)impl);

    return (Ellipse*)impl;
}

bool EllipseImpl::isTypeOf(const ObjectType &type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kEllipse) {
        return true;
    }
    return false;
}

void EllipseImpl::Delete()
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

QRectF EllipseImpl::getBoundingRect() const
{
    // {cx - rx, cy}, {cx + rx, cy}, {cx, cy - ry}, {cx, cy + ry}
    double cx = m_center.x();
    double cy = m_center.y();

    QRectF bounds{cx - m_radiusY, cy - m_radiusX, m_radiusY * 2, m_radiusX * 2};
    bounds = m_transform.mapRect(bounds);

    return bounds;
}

bool EllipseImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool EllipseImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

void EllipseImpl::setCenter(const QPointF& center)
{
    m_center = center;
}

QPointF EllipseImpl::getCenter() const
{
    return m_center;
}

void EllipseImpl::setRadiusX(double radiusX)
{
    m_radiusX = radiusX;
}

double EllipseImpl::getRadiusX() const
{
    return m_radiusX;
}

void EllipseImpl::setRadiusY(double radiusY)
{
    m_radiusY = radiusY;
}

double EllipseImpl::getRadiusY() const
{
    return m_radiusY;
}