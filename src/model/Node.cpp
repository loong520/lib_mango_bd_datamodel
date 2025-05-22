//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Node.h"
#include "impl/NodeImpl.h"
#include "impl/PinImpl.h"

using namespace mango::blockdiagram::datamodel;

Node* Node::New(Node* parent, bool isHierarchical, bool isRoot)
{
    return NodeImpl::New(parent, isHierarchical, isRoot);
}

QSizeF Node::getSize() const
{
    return impl_ptr(Node)->getSize();
}

void Node::setSize(const QSizeF &size)
{
    impl_ptr(Node)->setSize(size);
}

bool Node::isRootNode() const
{
    return impl_ptr(Node)->isRootNode();
}

bool Node::isHierarchical() const
{
    return impl_ptr(Node)->isHierarchical();
}

void Node::addGraphElement(GraphElement *graphElement)
{
    impl_ptr(Node)->addGraphElement((GraphElementImpl*)graphElement);
}

void Node::removeGraphElement(GraphElement *graphElement)
{
    impl_ptr(Node)->removeGraphElement((GraphElementImpl*)graphElement);
}

QList<GraphElement*> Node::getGraphElements() const
{
    auto &&elements = impl_ptr(Node)->getGraphElements();

    QList<GraphElement*> retElements;
    retElements.reserve(elements.size());
    for (auto element : elements) {
        retElements.append((GraphElement*)element);
    }
    return retElements;
}

QList<GraphElement*> Node::getGraphElements(ObjectType type) const
{
    auto &&elements = impl_ptr(Node)->getGraphElements();

    QList<GraphElement*> retElements;
    retElements.reserve(elements.size());
    for (auto element : elements) {
        if (element->isTypeOf(type)) {
            retElements.append((GraphElement*)element);
        }
    }
    return retElements;
}

void Node::addSubNode(Node *node)
{
    impl_ptr(Node)->addSubNode((NodeImpl*)node);
}

void Node::removeSubNode(Node *node)
{
    impl_ptr(Node)->removeSubNode((NodeImpl*)node);
}

QList<Node*> Node::getSubNodes() const
{
    auto &&nodes = impl_ptr(Node)->getSubNodes();

    QList<Node*> retNodes;
    retNodes.reserve(nodes.size());
    for (auto node : nodes) {
        retNodes.append((Node*)node);
    }
    return retNodes;
}

void Node::addIndependentPin(Pin *pin)
{
    impl_ptr(Node)->addIndependentPin((PinImpl*)pin);
}

void Node::removeIndependentPin(Pin *pin)
{
    impl_ptr(Node)->removeIndependentPin((PinImpl*)pin);
}

QList<Pin*> Node::getIndependentPin() const
{
    auto &&pins = impl_ptr(Node)->getIndependentPin();

    QList<Pin*> retPins;
    retPins.reserve(pins.size());
    for (auto pin : pins) {
        retPins.append((Pin*)pin);
    }
    return retPins;
}

void Node::addDevicePin(Pin *pin)
{
    impl_ptr(Node)->addDevicePin((PinImpl*)pin);
}

void Node::removeDevicePin(Pin *pin)
{
    impl_ptr(Node)->removeDevicePin((PinImpl*)pin);
}

QList<Pin*> Node::getDevicePins() const
{
    auto &&pins = impl_ptr(Node)->getDevicePins();

    QList<Pin*> retPins;
    retPins.reserve(pins.size());
    for (auto pin : pins) {
        retPins.append((Pin*)pin);
    }
    return retPins;
}

void Node::addNet(Net *net)
{
    impl_ptr(Node)->addNet((NetImpl*)net);
}

void Node::removeNet(Net *net)
{
    impl_ptr(Node)->removeNet((NetImpl*)net);
}

QList<Net*> Node::getNets() const
{
    auto &&nets = impl_ptr(Node)->getNets();

    QList<Net*> retNets;
    retNets.reserve(nets.size());
    for (auto net : nets) {
        retNets.append((Net*)net);
    }
    return retNets;
}

QList<GObject *> Node::items(const QPointF &pos) const
{
    auto &&items = impl_ptr(Node)->items(pos);

    QList<GObject *> retItems;
    retItems.reserve(items.size());
    for (auto item : items) {
        retItems.append((GObject*)item);
    }
    return retItems;
}

QList<GObject *> Node::items(const QRectF &rect) const
{
    auto &&items = impl_ptr(Node)->items(rect);

    QList<GObject *> retItems;
    retItems.reserve(items.size());
    for (auto item : items) {
        retItems.append((GObject*)item);
    }
    return retItems;
}
