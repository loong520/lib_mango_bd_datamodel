//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElementImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class PinImpl;
class Node;
class Symbol;

class SymbolImpl : public GraphElementImpl {
public:
    static Symbol *New(Node *parent);

    SymbolImpl(Object* parent = nullptr);

    void addPin(PinImpl* pin);
    void removePin(PinImpl* pin);
    QList<PinImpl*> getPins() const;

public:
    QList<PinImpl*> m_pins;
};

}
}
}