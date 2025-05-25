//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElementImpl.h"
#include "MangoBDDataModel/model/BDRTree.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class PinImpl;
class NetImpl;
class BDRTree;

class NodeImpl : public GraphElementImpl {
public:
    static NodeImpl* New(NodeImpl *parent, bool isHierarchical = false, bool isRoot = false);

    NodeImpl(Object* parent = nullptr, bool isHierarchical = false, bool isRoot = false);
    NodeImpl(const NodeImpl& other);
    NodeImpl* clone() const override;

    ObjectType getObjectType() const override { return ObjectType::kNode; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    bool isRootNode() const { return m_isRoot; }
    bool isHierarchical() const { return m_isHierarchical; }

    // node大小
    QSizeF getSize() const;
    void setSize(const QSizeF &size);

    // 子图元（node下的所有图元）
    void addGraphElement(GObjectImpl *element);
    void removeGraphElement(GObjectImpl *element);
    QList<GObjectImpl*> getGraphElements() const;

    // 子node
    void addSubNode(NodeImpl *node);
    void removeSubNode(NodeImpl *node);
    QList<NodeImpl*> getSubNodes() const { return m_subNodes; }

    // 独立的pin
    void addIndependentPin(PinImpl *pin);
    void removeIndependentPin(PinImpl *pin);
    QList<PinImpl*> getIndependentPin() const { return m_independentPins; }

    // 器件的pin
    void addDevicePin(PinImpl *pin);
    void removeDevicePin(PinImpl *pin);
    QList<PinImpl*> getDevicePins() const { return m_devicePins; }

    // 连线
    void addNet(NetImpl *net);
    void removeNet(NetImpl *net);
    QList<NetImpl*> getNets() const { return m_nets; }

    // 空间索引
    BDRTree& items() { return m_rtree; }
    const BDRTree& items() const { return m_rtree; }

    // 定位图元
    QList<GObjectImpl *> items(const QPointF &pos) const;
    QList<GObjectImpl *> items(const QRectF &rect) const;

public:
    bool m_isRoot = false;                  // 根节点
    bool m_isHierarchical = false;          // 层次节点
    QSizeF m_size;                          // 节点大小(用来保存根节点大小)
    QList<NodeImpl*> m_subNodes;            // 内部的子node
    QList<PinImpl*>  m_independentPins;     // 内部的子pin
    QList<PinImpl*>  m_devicePins;          // node or symbol边界上的pin
    QList<NetImpl*>  m_nets;                // 内部的连线
    BDRTree          m_rtree;               // 空间索引树，保存了所有图元
};

}
}
}