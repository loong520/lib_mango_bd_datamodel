//
// Created by 18224 on 2025/5/23.
//

#include "LibSymbolImpl.h"
#include "NodeImpl.h"
#include "PinImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

LibSymbol *LibSymbolImpl::New(Node *parent)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    LibSymbolImpl* impl = new LibSymbolImpl((Object*)parent);
    obj_impl_ptr(Node, parent)->addGraphElement(impl);
    return (LibSymbol*)impl;
}

LibSymbolImpl::LibSymbolImpl(Object* parent) : GraphElementImpl(parent)
{

}

bool LibSymbolImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kGraphElement ||
        typeId == ObjectType::kLibSymbol) {
        return true;
    }
    return false;
}

void LibSymbolImpl::Delete()
{
    if (!m_parent) {
        // TODO: LOG_ERROR
        return;
    }
    ObjectType::TypeId typeId = m_parent->getObjectType();
    if (typeId == ObjectType::kNode) {
        obj_impl_ptr(Node, m_parent)->removeGraphElement((LibSymbolImpl*)this);
    }
}

QRectF LibSymbolImpl::getBoundingRect() const
{
    QRectF bounds;
    if (m_shape) {
        auto shapeRect = m_shape->getBoundingRect();
        shapeRect = m_transform.mapRect(shapeRect);
        bounds |= shapeRect;
    }
    for (auto pin : m_pins) {
        auto pinRect = pin->getBoundingRect();
        pinRect = m_transform.mapRect(pinRect);
        bounds |= pinRect;
    }
    return bounds;
}

void LibSymbolImpl::addPin(PinImpl* pin)
{
    if (pin == nullptr) {
        return;
    }
    if (m_pins.contains(pin)) {
        return;
    }
    m_pins.append(pin);
    pin->setParent((Object*)this);
}

void LibSymbolImpl::removePin(PinImpl* pin)
{
    if (pin == nullptr) {
        return;
    }
    m_pins.removeAll(pin);
}

QList<PinImpl*> LibSymbolImpl::getPins() const
{
    return m_pins;
}