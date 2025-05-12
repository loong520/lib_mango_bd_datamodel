//
// Created by 18224 on 2025/5/7.
//

#include "GObjectImpl.h"
#include "GObject.h"

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

QRectF GObjectImpl::getBoundingRect() const
{
    return m_boundingRect;
}

void GObjectImpl::setRotation(int angle)
{
    m_rotation = angle;
}

void GObjectImpl::setRotation(QPointF center, int angle)
{
    // TODO: implement
}