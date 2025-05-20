//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElementImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class NodeImpl;
class PinImpl;
class NetImpl;
class NodeRTree;

class NodeImpl : public GraphElementImpl {
public:
    static Node* New(Node *parent);

    NodeImpl(Object* parent = nullptr);

    ObjectType getObjectType() const override { return ObjectType::kNode; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    void initNodeSize();

    bool isRootNode() const { return getParent() == nullptr; }
    bool isHierarchical() const { return m_subNodes.size() > 0; }

    // node大小
    QSize getSize() const;
    void setSize(const QSize &size);

    // 子图元（node下的所有图元）
    void addGraphElement(GraphElementImpl *graphElement);
    void removeGraphElement(GraphElementImpl *graphElement);
    QList<GraphElementImpl*> getGraphElements() const;

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

    // 定位图元
    QList<GObjectImpl *> items(const QPointF &pos) const;
    QList<GObjectImpl *> items(const QRectF &rect) const;

public:
    QList<GraphElementImpl*> m_allElements; // 节点内的所有子图元
    QList<NodeImpl*> m_subNodes;            // 内部的子node
    QList<PinImpl*>  m_independentPins;     // 内部的子pin
    QList<PinImpl*>  m_devicePins;          // node or symbol边界上的pin
    QList<NetImpl*>  m_nets;                // 内部的连线
    NodeRTree* m_rtree = nullptr;
};

}
}
}