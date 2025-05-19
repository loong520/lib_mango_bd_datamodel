//
// Created by 18224 on 2025/5/7.
//

#include "ElipseImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

Elipse* ElipseImpl::New(Shape* parent)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    ElipseImpl* impl = new ElipseImpl((Object*)parent);

    obj_impl_ptr(Shape, parent)->addSubShape((GObjectImpl*)impl);

    return (Elipse*)impl;
}

bool ElipseImpl::isTypeOf(const ObjectType &type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kElipse) {
        return true;
    }
    return false;
}

void ElipseImpl::Delete()
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

QRectF ElipseImpl::getBoundingRect() const
{
    // {cx - rx, cy}, {cx + rx, cy}, {cx, cy - ry}, {cx, cy + ry}
    double cx = m_center.x();
    double cy = m_center.y();
    QPointF pts[4] = {
        {cx - m_radiusX, m_radiusY},
        {cx + m_radiusX, m_radiusY},
        {cx, cy - m_radiusY},
        {cx, cy + m_radiusY}
    };
    QRectF bounds;
    for (int i = 0; i < 4; ++i) {
        QPointF pt = m_transform.map(pts[i]);
        if (i == 0) {
            bounds = QRectF(pt, pt);
        } else {
            bounds = bounds.united(QRectF(pt, pt));
        }
    }
    return bounds;
}

void ElipseImpl::setCenter(const QPointF& center)
{
    m_center = center;
}

QPointF ElipseImpl::getCenter() const
{
    return m_center;
}

void ElipseImpl::setRadiusX(double radiusX)
{
    m_radiusX = radiusX;
}

double ElipseImpl::getRadiusX() const
{
    return m_radiusX;
}

void ElipseImpl::setRadiusY(double radiusY)
{
    m_radiusY = radiusY;
}

double ElipseImpl::getRadiusY() const
{
    return m_radiusY;
}