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
class NetImpl;
class CompositePin;

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

    // 传入的连线
    void addIncomingNet(NetImpl* net);
    void removeIncomingNet(NetImpl* net);
    QList<NetImpl*> getIncomingNets() const;

    // 输出的连线
    void addOutgoingNet(NetImpl* net);
    void removeOutgoingNet(NetImpl* net);
    QList<NetImpl*> getOutgoingNets() const;

    // 形状
    void setShapeType(PinShape shapeType);
    PinShape getShapeType() const;

    // 方向
    void setDirection(Direction direction);
    Direction getDirection() const;

public:
    QList<NetImpl*> m_incomingNets;
    QList<NetImpl*> m_outgoingNets;

    PinShape m_shapeType = Line;
    Direction m_direction = Left;

    CompositePin* m_compositePin = nullptr;
};

}
}
}