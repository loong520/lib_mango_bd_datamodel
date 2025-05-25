//
// Created by 18224 on 2025/5/7.
//

#include "PolygonImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

PolygonImpl* PolygonImpl::New(ShapeImpl* parent)
{
    return New(parent, {});
}

PolygonImpl* PolygonImpl::New(ShapeImpl* parent, const QList<QPointF> &v)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (v.isEmpty() || v.first() == v.last()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PolygonImpl* impl = new PolygonImpl(v, (Object*)parent);
    parent->addSubShape((GObjectImpl*)impl);

    return impl;
}

PolygonImpl::PolygonImpl(const PolygonImpl& other ): GObjectImpl(other), QList<QPointF>(other)
{
}

PolygonImpl* PolygonImpl::clone() const
{
    return new PolygonImpl(*this);
}

bool PolygonImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kPolygon) {
        return true;
    }
    return false;
}

void PolygonImpl::Delete()
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

QRectF PolygonImpl::getBoundingRect() const
{
    QPolygonF poly(toVector());

    QRectF bounds = poly.boundingRect();

    inflateAndTransform(bounds);

    return bounds;
}

bool PolygonImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool PolygonImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

QPolygonF PolygonImpl::toQPolygon() const
{
    QPolygonF poly(this->toVector());
    return poly;
}

void PolygonImpl::append(const QPointF &p)
{
    QList<QPointF>::append(p);
}

void PolygonImpl::append(const QList<QPointF> &points)
{
    QList<QPointF>::append(points);
}

void PolygonImpl::prepend(const QPointF &p)
{
    QList<QPointF>::prepend(p);
}

void PolygonImpl::replace(int index, const QPointF &p)
{
    QList<QPointF>::replace(index, p);
}

// 删除点
void PolygonImpl::removeAt(int i)
{
    QList<QPointF>::removeAt(i);
}

void PolygonImpl::removeFirst()
{
    QList<QPointF>::removeFirst();
}
void PolygonImpl::removeLast()
{
    QList<QPointF>::removeLast();
}

void PolygonImpl::clear()
{
    QList<QPointF>::clear();
}