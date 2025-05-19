//
// Created by 18224 on 2025/5/7.
//

#include "ArcImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

Arc* ArcImpl::New(Shape* parent)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    ArcImpl* impl = new ArcImpl((Object*)parent);

    obj_impl_ptr(Shape, parent)->addSubShape((GObjectImpl*)impl);

    return (Arc*)impl;
}

bool ArcImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kArc) {
        return true;
    }
    return false;
}

void ArcImpl::Delete()
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

QRectF ArcImpl::getBoundingRect() const
{
    QRectF bounds;
    int steps = 32;
    float step = m_spanAngle / steps;
    for (int i = 0; i <= steps; ++i) {
        float angle = (m_startAngle + i * step) * (3.1415926f / 180.0f);
        float x = m_center.x() + m_radius * std::cos(angle);
        float y = m_center.y() + m_radius * std::sin(angle);
        QPointF pt = m_transform.map(QPointF(x, y));
        if (i == 0) {
            bounds = QRectF(pt, pt);
        } else {
            bounds = bounds.united(QRectF(pt, pt));
        }
    }
    return bounds;
}

void ArcImpl::setCenter(const QPointF center)
{
    m_center = center;
}

QPointF ArcImpl::getCenter() const
{
    return m_center;
}

void ArcImpl::setRadius(double radius)
{
    m_radius = radius;
}

double ArcImpl::getRadius() const
{
    return m_radius;
}

void ArcImpl::setStartAngle(double startAngle)
{
    m_startAngle = startAngle;
}

double ArcImpl::getStartAngle() const
{
    return m_startAngle;
}

void ArcImpl::setSpanAngle(double spanAngle)
{
    m_spanAngle = spanAngle;
}

double ArcImpl::getSpanAngle() const
{
    return m_spanAngle;
}