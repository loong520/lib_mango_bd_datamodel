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

    ObjectType getObjectType() const override { return ObjectType::kSymbol; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    void addPin(PinImpl* pin);
    void removePin(PinImpl* pin);
    QList<PinImpl*> getPins() const;

public:
    QList<PinImpl*> m_pins;
};

}
}
}