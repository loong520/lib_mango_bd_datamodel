//
// Created by 18224 on 2025/5/7.
//

#include "Symbol.h"
#include "SymbolImpl.h"
#include "PinImpl.h"

using namespace mango::blockdiagram::datamodel;

Symbol *Symbol::New(Node *parent)
{
    return SymbolImpl::New(parent);
}

void Symbol::addPin(Pin* pin)
{
    impl_ptr(Symbol)->addPin((PinImpl*)pin);
}

void Symbol::removePin(Pin* pin)
{
    impl_ptr(Symbol)->removePin((PinImpl*)pin);
}

QList<Pin*> Symbol::getPins() const
{
    /// 可能影响性能，后面修改为不要转换
    QList<Pin*> pins;
    for (auto pin : impl_ptr(Symbol)->getPins()) {
        pins.append((Pin*)pin);
    }
    return pins;
}