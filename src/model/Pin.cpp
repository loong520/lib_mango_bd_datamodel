//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Pin.h"
#include "impl/PinImpl.h"

using namespace mango::blockdiagram::datamodel;

Pin* Pin::New(Node* parent, const QString& name, bool inBoundary)
{
    return PinImpl::New(parent, name, inBoundary);
}

Pin* Pin::New(Symbol* parent, const QString& name)
{
    return PinImpl::New(parent, name);
}

void Pin::setName(const QString& name)
{
    impl_ptr(Pin)->setName(name);
}

QString Pin::getName() const
{
    return impl_ptr(Pin)->getName();
}

void Pin::addIncomingNet(Net* net)
{
    impl_ptr(Pin)->addIncomingNet((NetImpl*)net);
}

void Pin::removeIncomingNet(Net* net)
{
    impl_ptr(Pin)->removeIncomingNet((NetImpl*)net);
}

QList<Net*> Pin::getIncomingNets() const
{
    QList<Net*> nets;
    for (auto net : impl_ptr(Pin)->getIncomingNets()) {
        nets.append((Net*)net);
    }
    return nets;
}

void Pin::addOutgoingNet(Net* net)
{
    impl_ptr(Pin)->addOutgoingNet((NetImpl*)net);
}

void Pin::removeOutgoingNet(Net* net)
{
    impl_ptr(Pin)->removeOutgoingNet((NetImpl*)net);
}

QList<Net*> Pin::getOutgoingNets() const
{
    QList<Net*> nets;
    for (auto net : impl_ptr(Pin)->getOutgoingNets()) {
        nets.append((Net*)net);
    }
    return nets;
}

void Pin::setShapeType(PinShape shapeType)
{
    impl_ptr(Pin)->setShapeType(shapeType);
}

PinShape Pin::getShapeType() const
{
    return impl_ptr(Pin)->getShapeType();
}

void Pin::setDirection(Direction direction)
{
    impl_ptr(Pin)->setDirection(direction);
}

Direction Pin::getDirection() const
{
    return impl_ptr(Pin)->getDirection();
}