//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Node.h"
#include "impl/NodeImpl.h"
#include "impl/PinImpl.h"

using namespace mango::blockdiagram::datamodel;

Node* Node::New(Node* parent)
{
    return NodeImpl::New(parent);
}

void Node::initNodeSize()
{
    impl_ptr(Node)->initNodeSize();
}

QSize Node::getSize() const
{
    return impl_ptr(Node)->getSize();
}

void Node::setSize(const QSize &size)
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
    QList<GraphElement*> elements;
    for (auto element : impl_ptr(Node)->getGraphElements()) {
        elements.append((GraphElement*)element);
    }
    return elements;
}

QList<GraphElement*> Node::getGraphElements(ObjectType type) const
{
    QList<GraphElement*> elements;
    for (auto element : impl_ptr(Node)->getGraphElements()) {
        if (element->isTypeOf(type)) {
            elements.append((GraphElement*)element);
        }
    }
    return elements;
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
    QList<Node*> nodes;
    for (auto node : impl_ptr(Node)->getSubNodes()) {
        nodes.append((Node*)node);
    }
    return nodes;
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
    QList<Pin*> pins;
    for (auto pin : impl_ptr(Node)->getIndependentPin()) {
        pins.append((Pin*)pin);
    }
    return pins;
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
    QList<Pin*> pins;
    for (auto pin : impl_ptr(Node)->getDevicePins()) {
        pins.append((Pin*)pin);
    }
    return pins;
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
    QList<Net*> nets;
    for (auto net : impl_ptr(Node)->getNets()) {
        nets.append((Net*)net);
    }
    return nets;
}

QList<GObject *> Node::items(const QPointF &pos) const
{
    QList<GObject *> items;
    for (auto item : impl_ptr(Node)->items(pos)) {
        items.append((GObject*)item);
    }
    return items;
}

QList<GObject *> Node::items(const QRectF &rect) const
{
    QList<GObject *> items;
    for (auto item : impl_ptr(Node)->items(rect)) {
        items.append((GObject*)item);
    }
    return items;
}
