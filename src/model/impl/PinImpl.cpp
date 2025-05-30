//
// Created by 18224 on 2025/5/7.
//

#include "PinImpl.h"
#include "NodeImpl.h"
#include "SymbolImpl.h"
#include "LibSymbolImpl.h"
#include "LabelImpl.h"

using namespace mango::blockdiagram::datamodel;

PinImpl* PinImpl::New(NodeImpl* parent, const QString& name, bool isDevicePin)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PinImpl* impl = new PinImpl(name, isDevicePin, (Object*)parent);

    if (isDevicePin) {
        parent->addDevicePin(impl);
    } else {
        parent->addIndependentPin(impl);
    }
    return impl;
}

PinImpl* PinImpl::New(LibSymbolImpl* parent, const QString& name)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PinImpl* impl = new PinImpl(name, true, (Object*)parent);
    parent->addPin(impl);
    return impl;
}

PinImpl* PinImpl::New(SymbolImpl* parent, const QString& name)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PinImpl* impl = new PinImpl(name, true, (Object*)parent);
    parent->addPin(impl);
    return impl;
}

PinImpl::PinImpl(const QString& name, bool isDevicePin, Object* parent) : GraphElementImpl(parent)
{
    // 创建一个名字label
    LabelImpl* label = new LabelImpl((Object*)this);
    label->setText(name);
    addLabel(label);

    m_isDevicePin = isDevicePin;
}

PinImpl::PinImpl(const PinImpl &other) : GraphElementImpl(other)
{
    m_incomingNets = other.m_incomingNets;
    m_outgoingNets = other.m_outgoingNets;

    m_shapeType = other.m_shapeType;
    m_direction = other.m_direction;
    m_isDevicePin = other.m_isDevicePin;
    m_compositePin = other.m_compositePin;
    m_libPin = other.m_libPin;
}

PinImpl* PinImpl::clone() const
{
    return new PinImpl(*this);
}

bool PinImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kGraphElement ||
        typeId == ObjectType::kPin) {
        return true;
    }
    return false;
}

void PinImpl::Delete()
{

}

QRectF PinImpl::getBoundingRect() const
{
    if (m_libPin) {
        return m_libPin->getBoundingRect();
    }
    return getBoundingRect();
}

bool PinImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool PinImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

void PinImpl::setName(const QString& name)
{
    auto nameLabel = GraphElementImpl::findMainName(this);
    if (nameLabel) {
        nameLabel->setText(name);
    }
}

QString PinImpl::getName() const
{
    if (m_libPin) {
        return m_libPin->getName();
    }
    auto nameLabel = GraphElementImpl::findMainName(this);
    if (nameLabel) {
        return nameLabel->getText();
    }
    return "";
}

ShapeImpl *PinImpl::getShape() const
{
    if (m_libPin) {
        return m_libPin->getShape();
    }
    return m_shape;
}

void PinImpl::addIncomingNet(NetImpl* net)
{
    if (net == nullptr) {
        // TODO: LOG_WARN
        return;
    }
    if (getIncomingNets().contains(net)) {
        return;
    }
    m_incomingNets.append(net);
}

void PinImpl::removeIncomingNet(NetImpl* net)
{
    if (net == nullptr) {
        // TODO: LOG_WARN
        return;
    }
    m_incomingNets.removeAll(net);
}

QList<NetImpl*> PinImpl::getIncomingNets() const
{
    return m_incomingNets;
}

void PinImpl::addOutgoingNet(NetImpl* net)
{
    if (net == nullptr) {
        // TODO: LOG_WARN
        return;
    }
    if (getOutgoingNets().contains(net)) {
        return;
    }
    m_outgoingNets.append(net);
}

void PinImpl::removeOutgoingNet(NetImpl* net)
{
    if (net == nullptr) {
        // TODO: LOG_WARN
        return;
    }
    m_outgoingNets.removeAll(net);
}

QList<NetImpl*> PinImpl::getOutgoingNets() const
{
    return m_outgoingNets;
}

void PinImpl::setShapeType(PinShape shapeType)
{
    if (m_shapeType == shapeType) {
        return;
    }
    m_shapeType = shapeType;

    // todo: 更新shape数据
}

PinShape PinImpl::getShapeType() const
{
    if (m_libPin) {
        return m_libPin->getShapeType();
    }
    return m_shapeType;
}

void PinImpl::setDirection(Direction direction)
{
    if (m_direction == direction) {
        return;
    }
    m_direction = direction;
}

Direction PinImpl::getDirection() const
{
    if (m_libPin) {
        return m_libPin->getDirection();
    }
    return m_direction;
}