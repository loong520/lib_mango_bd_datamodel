//
// Created by 18224 on 2025/5/7.
//

#include "PinImpl.h"
#include "NodeImpl.h"
#include "SymbolImpl.h"
#include "LabelImpl.h"

using namespace mango::blockdiagram::datamodel;

Pin* PinImpl::New(Node* parent, const QString& name, bool inBoundary)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PinImpl* impl = new PinImpl(name, (Object*)parent);

    if (inBoundary) {
        obj_impl_ptr(Node, parent)->addBoundaryPin(impl);
    } else {
        obj_impl_ptr(Node, parent)->addInternalPin(impl);
    }
    return (Pin*)impl;
}

Pin* PinImpl::New(Symbol* parent, const QString& name)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PinImpl* impl = new PinImpl(name, (Object*)parent);
    obj_impl_ptr(Symbol, parent)->addPin(impl);
    return (Pin*)impl;
}

PinImpl::PinImpl(const QString& name, Object* parent) : GraphElementImpl(parent)
{
    // 创建一个名字label
    LabelImpl* label = new LabelImpl((Object*)this);
    label->setText(name);
    addLabel(label);
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
    return getBoundingRect();
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
    auto nameLabel = GraphElementImpl::findMainName(this);
    if (nameLabel) {
        return nameLabel->getText();
    }
    return "";
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
    m_shapeType = shapeType;

    // todo: 更新shape数据
}

PinShape PinImpl::getShapeType() const
{
    return m_shapeType;
}

void PinImpl::setDirection(Direction direction)
{
    m_direction = direction;
}

Direction PinImpl::getDirection() const
{
    return m_direction;
}