//
// Created by 18224 on 2025/5/23.
//
#pragma once

#include "GraphElementImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Node;
class LibSymbol;
class PinImpl;

class LibSymbolImpl : public GraphElementImpl {
public:
    static LibSymbol *New(Node *parent);

    LibSymbolImpl(Object* parent = nullptr);

    ObjectType getObjectType() const override { return ObjectType::kLibSymbol; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    void addPin(PinImpl* pin);
    void removePin(PinImpl* pin);
    QList<PinImpl*> getPins() const;

public:
    QList<PinImpl*> m_pins;
};

}
}
}
