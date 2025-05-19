//
// Created by 18224 on 2025/5/7.
//

#include "PolygonImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

Polygon* PolygonImpl::New(Shape* parent)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PolygonImpl* impl = new PolygonImpl((Object*)parent);

    obj_impl_ptr(Shape, parent)->addSubShape((GObjectImpl*)impl);

    return (Polygon*)impl;
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
    QRectF bounds;
    for (int i = 0; i < m_points.size(); ++i) {
        QPointF pt = m_transform.map(m_points[i]);
        if (i == 0) {
            bounds = QRectF(pt, pt);
        } else {
            bounds = bounds.united(QRectF(pt, pt));
        }
    }
    return bounds;
}