//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Net.h"
#include "impl/NetImpl.h"

using namespace mango::blockdiagram::datamodel;

Net* Net::New(Node* parent)
{
    return NetImpl::New(parent);
}

void Net::addSource(Pin* pin)
{
    impl_ptr(Net)->addSource((PinImpl*)pin);
}

void Net::removeSource(Pin* pin)
{
    impl_ptr(Net)->removeSource((PinImpl*)pin);
}

QList<Pin*> Net::getSources() const
{
    QList<Pin*> sources;
    for (auto source : impl_ptr(Net)->getSources()) {
        sources.append((Pin*)source);
    }
    return sources;
}

void Net::addTarget(Pin* pin)
{
    impl_ptr(Net)->addTarget((PinImpl*)pin);
}

void Net::removeTarget(Pin* pin)
{
    impl_ptr(Net)->removeTarget((PinImpl*)pin);
}

QList<Pin*> Net::getTargets() const
{
    QList<Pin*> targets;
    for (auto target : impl_ptr(Net)->getTargets()) {
        targets.append((Pin*)target);
    }
    return targets;
}

void Net::setConnectMode(ConnectMode mode)
{
    impl_ptr(Net)->setConnectMode(mode);
}

ConnectMode Net::getConnectMode() const
{
    return impl_ptr(Net)->getConnectMode();
}

int Net::getLineWidth() const
{
    return impl_ptr(Net)->getLineWidth();
}

QString Net::getLineColor() const
{
    return impl_ptr(Net)->getLineColor();
}
