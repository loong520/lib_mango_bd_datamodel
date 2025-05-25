//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Symbol.h"
#include "impl/SymbolImpl.h"
#include "impl/LibSymbolImpl.h"
#include "impl/PinImpl.h"

using namespace mango::blockdiagram::datamodel;

Symbol *Symbol::New(Node *parent, LibSymbol *libSymbol)
{
    return (Symbol*)SymbolImpl::New((NodeImpl*)parent, (LibSymbolImpl*)libSymbol);
}

void Symbol::setLibSymbol(LibSymbol *aLibSymbol)
{
    impl_ptr(Symbol)->setLibSymbol((LibSymbolImpl*)aLibSymbol);
}

LibSymbol *Symbol::getLibSymbol() const
{
    return (LibSymbol*)impl_ptr(Symbol)->getLibSymbol();
}

QList<Pin*> Symbol::getPins() const
{
    auto &&pins = impl_ptr(Symbol)->getPins();

    QList<Pin*> retPins;
    retPins.reserve(pins.size());
    for (auto pin : pins) {
        retPins.append((Pin*)pin);
    }
    return retPins;
}

void Symbol::updatePins()
{
    impl_ptr(Symbol)->updatePins();
}