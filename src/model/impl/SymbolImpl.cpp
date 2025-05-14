//
// Created by 18224 on 2025/5/7.
//

#include "SymbolImpl.h"
#include "NodeImpl.h"
#include "PinImpl.h"

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