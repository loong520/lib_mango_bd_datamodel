//
// Created by 18224 on 2025/5/7.
//

#include "SymbolImpl.h"
#include "NodeImpl.h"
#include "PinImpl.h"
#include "ShapeImpl.h"
#include <QSet>

using namespace mango::blockdiagram::datamodel;

SymbolImpl *SymbolImpl::New(NodeImpl *parent, LibSymbolImpl *libSymbol)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    SymbolImpl* impl = new SymbolImpl(libSymbol, (Object*)parent);
    parent->addGraphElement(impl);
    return impl;
}

SymbolImpl::SymbolImpl(const SymbolImpl &other) : GraphElementImpl(other)
{
    m_libSymbol = other.m_libSymbol;

    if (other.m_pins.size() > 0) {
        m_pins.reserve(other.m_pins.size());
        for (auto pin : other.m_pins) {
            PinImpl* newPin = pin->clone();
            m_pins.append(newPin);
        }
    }
    // todo : m_pinMap
    // QHash<PinImpl*, PinImpl*> m_pinMap;     // LibSymbol的pin指针 : Symbol的pin指针
}

SymbolImpl *SymbolImpl::clone() const
{
    return new SymbolImpl(*this);
}

bool SymbolImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kGraphElement ||
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

void SymbolImpl::setLibSymbol(LibSymbolImpl *aLibSymbol)
{
    m_libSymbol = aLibSymbol;

    updatePins();
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

void SymbolImpl::updatePins()
{
    QHash<QString, PinImpl*> pinNameMap;
    QSet<PinImpl*>           unassignedSchPins;
    QSet<PinImpl*>           unassignedLibPins;

    for (auto pin : m_pins) {
        pinNameMap[pin->getName()] = pin;
        unassignedSchPins.insert(pin);
        pin->setLibPin(nullptr);
    }
    m_pinMap.clear();
    if (!m_libSymbol) {
        return;
    }
    for (auto libPin : m_libSymbol->getPins()) {
        PinImpl* pin = nullptr;

        auto it = pinNameMap.find(libPin->getName()); // 使用pin的名字匹配
        if (it != pinNameMap.end()) {
            unassignedLibPins.insert(libPin);
            continue;
        }
        pin = *it;
        pinNameMap.erase(it);
        pin->setLibPin(libPin);
        pin->setPos(libPin->getPos());

        unassignedSchPins.remove(pin);
        m_pinMap[libPin] = pin;
    }

    // 添加库符号中未没有匹配到的引脚
    for (auto libPin : unassignedLibPins) {
        PinImpl* pin = nullptr;

        // 首先尝试重新使用现有的引脚
        if (!unassignedSchPins.empty()) {
            auto it = unassignedSchPins.begin();
            pin = *it;
            unassignedSchPins.erase(it);
        } else {
            // 这是一个未找到的引脚，所以创建一个新的引脚。
            pin = PinImpl::New(this, libPin->getName());
        }
        m_pinMap[libPin] = pin;
        pin->setLibPin(libPin);
        pin->setPos(libPin->getPos());
        pin->setName(libPin->getName());
    }

    // 如果符号中还有未匹配到库符号引脚的引脚，则将其移除
    for (auto it1 = m_pins.begin(); it1 != m_pins.end() && !unassignedSchPins.empty();) {
        auto it2 = unassignedSchPins.find(*it1);
        if (it2 != unassignedSchPins.end()) {
            it1 = m_pins.erase(it1);
            unassignedSchPins.erase(it2);
        } else {
            ++it1;
        }
    }
}