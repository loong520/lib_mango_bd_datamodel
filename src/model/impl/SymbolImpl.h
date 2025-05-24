//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElementImpl.h"
#include "LibSymbolImpl.h"
#include <QHash>

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Node;
class Symbol;
class LibSymbolImpl;
class PinImpl;

class SymbolImpl : public GraphElementImpl {
public:
    static Symbol *New(Node *parent, LibSymbolImpl *libSymbol);

    SymbolImpl(LibSymbolImpl *libSymbol, Object* parent = nullptr)
        : GraphElementImpl(parent), m_libSymbol(libSymbol)
    {}

    ObjectType getObjectType() const override { return ObjectType::kSymbol; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    void setLibSymbol(LibSymbolImpl *aLibSymbol);
    LibSymbolImpl *getLibSymbol() const { return m_libSymbol; }

    QList<PinImpl*> getPins() const { return m_pins; }
    void updatePins();

public:
    LibSymbolImpl* m_libSymbol = nullptr;   ///< 库符号对象指针
    QList<PinImpl*> m_pins;                 ///< 每个 PIN 对应一个LibSymbol的PIN
    QHash<PinImpl*, PinImpl*> m_pinMap;     ///< LibSymbol的pin指针 : Symbol的pin指针
};

}
}
}