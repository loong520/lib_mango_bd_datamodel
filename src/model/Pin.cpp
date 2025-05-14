//
// Created by 18224 on 2025/5/7.
//

#include "Pin.h"
#include "PinImpl.h"

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