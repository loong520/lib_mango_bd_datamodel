//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElementImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class NodeImpl;
class SymbolImpl;
class LibSymbolImpl;
class NetImpl;
class CompositePinImpl;

class PinImpl : public GraphElementImpl {
public:
    static PinImpl* New(NodeImpl* parent, const QString& name, bool isDevicePin = true);
    static PinImpl* New(LibSymbolImpl* parent, const QString& name);
    static PinImpl* New(SymbolImpl* parent, const QString& name);

    PinImpl(const QString& name, bool isDevicePin = true, Object* parent = nullptr);
    PinImpl(const PinImpl &other);
    PinImpl* clone() const override;

    ObjectType getObjectType() const override { return ObjectType::kPin; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    void setName(const QString& name);
    QString getName() const;

    ShapeImpl *getShape() const;

    /// 库引脚
    void setLibPin(PinImpl* libPin) { m_libPin = libPin; }
    PinImpl* getLibPin() const { return m_libPin; }

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

    PinShape            m_shapeType = Line;
    Direction           m_direction = Left;
    bool                m_isDevicePin;        // 是否是器件的引脚(在块图中用来区别于模块端口和实例端口,原理图中都应该是器件的引脚)
    CompositePinImpl*   m_compositePin = nullptr;
    PinImpl*            m_libPin = nullptr;   // 原理图中引脚对应的库引脚
};

}
}
}