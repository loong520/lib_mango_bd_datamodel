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

    QSize getSize() const;
    void setSize(const QSize &size);

    void addGraphElement(GraphElementImpl *graphElement);
    void removeGraphElement(GraphElementImpl *graphElement);
    QList<GraphElementImpl*> getGraphElements() const { return m_elements; }

    void addSubNode(NodeImpl *node);
    void removeSubNode(NodeImpl *node);
    QList<NodeImpl*> getSubNodes() const { return m_subNodes; }

    void addInternalPin(PinImpl *pin);
    void removeInternalPin(PinImpl *pin);
    QList<PinImpl*> getInternalPins() const { return m_internalPins; }

    void addBoundaryPin(PinImpl *pin);
    void removeBoundaryPin(PinImpl *pin);
    QList<PinImpl*> getBoundaryPins() const { return m_boundaryPins; }

    void addNet(NetImpl *net);
    void removeNet(NetImpl *net);
    QList<NetImpl*> getNets() const { return m_nets; }

public:
    QList<GraphElementImpl*> m_elements;// 内部的子元素
    QList<NodeImpl*> m_subNodes;        // 内部的子node
    QList<PinImpl*>  m_internalPins;    // 内部的子pin
    QList<PinImpl*>  m_boundaryPins;    // node or symbol边界上的pin
    QList<NetImpl*>  m_nets;            // 内部的连线
    NodeRTree* m_rtree = nullptr;
};

}
}
}