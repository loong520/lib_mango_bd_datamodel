//
// Created by 18224 on 2025/5/7.
//

#include "PolylineImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

Polyline* PolylineImpl::New(Shape* parent)
{
    return New(parent, {});
}

Polyline* PolylineImpl::New(Shape* parent, const QList<QPointF> &v)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PolylineImpl* impl = new PolylineImpl(v, (Object*)parent);

    obj_impl_ptr(Shape, parent)->addSubShape((GObjectImpl*)impl);

    return (Polyline*)impl;
}

bool PolylineImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kPolyline) {
        return true;
    }
    return false;
}

void PolylineImpl::Delete()
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

QRectF PolylineImpl::getBoundingRect() const
{
    QPolygonF poly(toVector());

    QRectF bounds = poly.boundingRect();

    inflateAndTransform(bounds);

    return bounds;
}

bool PolylineImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool PolylineImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

void PolylineImpl::append(const QPointF &p)
{
    QList<QPointF>::append(p);
}

void PolylineImpl::append(const QList<QPointF> &points)
{
    QList<QPointF>::append(points);
}

void PolylineImpl::prepend(const QPointF &p)
{
    QList<QPointF>::prepend(p);
}

void PolylineImpl::replace(int index, const QPointF &p)
{
    QList<QPointF>::replace(index, p);
}

// 删除点
void PolylineImpl::removeAt(int i)
{
    QList<QPointF>::removeAt(i);
}

void PolylineImpl::removeFirst()
{
    QList<QPointF>::removeFirst();
}
void PolylineImpl::removeLast()
{
    QList<QPointF>::removeLast();
}

void PolylineImpl::clear()
{
    QList<QPointF>::clear();
}