//
// Created by 18224 on 2025/5/23.
//

#include "MangoBDDataModel/model/LibSymbol.h"
#include "impl/LibSymbolImpl.h"

using namespace mango::blockdiagram::datamodel;

LibSymbol *LibSymbol::New(Node *parent)
{
    return (LibSymbol*)LibSymbolImpl::New((NodeImpl*)parent);
}

LibSymbol *LibSymbol::clone() const
{
    return (LibSymbol*)impl_ptr(LibSymbol)->clone();
}

void LibSymbol::addPin(Pin* pin)
{
    impl_ptr(LibSymbol)->addPin((PinImpl*)pin);
}

void LibSymbol::removePin(Pin* pin)
{
    impl_ptr(LibSymbol)->removePin((PinImpl*)pin);
}

QList<Pin*> LibSymbol::getPins() const
{
    /// 可能影响性能，后面修改为不要转换
    QList<Pin*> pins;
    for (auto pin : impl_ptr(LibSymbol)->getPins()) {
        pins.append((Pin*)pin);
    }
    return pins;
}
