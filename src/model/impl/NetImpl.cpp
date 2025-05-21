//
// Created by 18224 on 2025/5/7.
//

#include "NetImpl.h"
#include "NodeImpl.h"

using namespace mango::blockdiagram::datamodel;

Net* NetImpl::New(Node* parent)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    NetImpl* net = new NetImpl((Object*)parent);
    obj_impl_ptr(Node, parent)->addNet((NetImpl*)net);
    return (Net*)net;
}

NetImpl::NetImpl(Object* parent) : GraphElementImpl(parent)
{
}

bool NetImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool NetImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

void NetImpl::addSource(PinImpl* pin)
{
    if (pin == nullptr) {
        return;
    }
    if (m_sources.contains(pin)) {
        return;
    }
    m_sources.append(pin);
}

void NetImpl::removeSource(PinImpl* pin)
{
    if (pin == nullptr) {
        return;
    }
    m_sources.removeAll(pin);
}

QList<PinImpl*> NetImpl::getSources() const
{
    return m_sources;
}

void NetImpl::addTarget(PinImpl* pin)
{
    if (pin == nullptr) {
        return;
    }
    if (m_targets.contains(pin)) {
        return;
    }
    m_targets.append(pin);
}

void NetImpl::removeTarget(PinImpl* pin)
{
    if (pin == nullptr) {
        return;
    }
    m_targets.removeAll(pin);
}

QList<PinImpl*> NetImpl::getTargets() const
{
    return m_targets;
}

void NetImpl::setConnectMode(ConnectMode mode)
{
    m_connectMode = mode;
}

ConnectMode NetImpl::getConnectMode() const
{
    return m_connectMode;
}

int NetImpl::getLineWidth() const
{
    return 1;
    // todo: query from StyleManager
}

QString NetImpl::getLineColor() const
{
    return "#7BCC7B";
    // todo: query from StyleManager
}