//
// Created by 18224 on 2025/5/7.
//

#include "SymbolImpl.h"
#include "NodeImpl.h"
#include "PinImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

Symbol *SymbolImpl::New(Node *parent)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    SymbolImpl* impl = new SymbolImpl((Object*)parent);
    obj_impl_ptr(Node, parent)->addGraphElement(impl);
    return (Symbol*)impl;
}

SymbolImpl::SymbolImpl(Object* parent) : GraphElementImpl(parent)
{

}

bool SymbolImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kSymbol) {
        return true;
    }
    return false;
}

void SymbolImpl::Delete()
{
    if (!m_parent) {
        // TODO: LOG_ERROR
        return;
    }
    ObjectType::TypeId typeId = m_parent->getObjectType();
    if (typeId == ObjectType::kNode) {
        obj_impl_ptr(Node, m_parent)->removeGraphElement((SymbolImpl*)this);
    }
}

QRectF SymbolImpl::getBoundingRect() const
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

bool SymbolImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool SymbolImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

void SymbolImpl::addPin(PinImpl* pin)
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

void SymbolImpl::removePin(PinImpl* pin)
{
    if (pin == nullptr) {
        return;
    }
    m_pins.removeAll(pin);
}

QList<PinImpl*> SymbolImpl::getPins() const
{
    return m_pins;
}