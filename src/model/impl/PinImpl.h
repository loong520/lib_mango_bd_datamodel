//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElementImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Pin;
class Node;
class Symbol;

class PinImpl : public GraphElementImpl {
public:
    static Pin* New(Node* parent, const QString& name, bool inBoundary);
    static Pin* New(Symbol* parent, const QString& name);

    PinImpl(const QString& name, Object* parent = nullptr);

    ObjectType getObjectType() const override { return ObjectType::kPin; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    void setName(const QString& name);
    QString getName() const;
};

}
}
}