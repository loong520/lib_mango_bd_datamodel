//
// Created by 18224 on 2025/5/7.
//

#include "NodeImpl.h"
#include "ShapeImpl.h"
#include "RectangleImpl.h"
#include "Rectangle.h"
#include "PinImpl.h"
#include "NetImpl.h"

using namespace mango::blockdiagram::datamodel;

Node* NodeImpl::New(Node *parent)
{
    NodeImpl* impl = new NodeImpl((Object*)parent);
    if (parent) {
        impl->initNodeSize();
        obj_impl_ptr(Node, parent)->addGraphElement((GraphElementImpl*)impl);
    }
    return (Node*)impl;
}

NodeImpl::NodeImpl(Object* parent) : GraphElementImpl(parent)
{
}

bool NodeImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kGraphElement ||
        typeId == ObjectType::kNode) {
        return true;
    }
    return false;
}

void NodeImpl::Delete()
{

}

QRectF NodeImpl::getBoundingRect() const
{
    QRectF rect;
    if (isRootNode()) {
        // 根节点的边界矩形为所有子节点的边界矩形的并集
        for (auto element : m_elements) {
            auto elementRect = element->getBoundingRect();
            rect = rect.united(elementRect);
        }
        for (auto pin : m_internalPins) {
            auto pinRect = pin->getBoundingRect();
            rect = rect.united(pinRect);
        }
        for (auto net : m_nets) {
            auto netRect = net->getBoundingRect();
            rect = rect.united(netRect);
        }
    } else {
        // 非根节点的边界矩形为节点边界矩形和节点上pin边界矩形的并集
        if (m_shape) {
            auto shapeRect = m_shape->getBoundingRect();
            rect = rect.united(shapeRect);
        }
        for (auto pin : m_boundaryPins) {
            auto pinRect = pin->getBoundingRect();
            rect = rect.united(pinRect);
        }
    }
    return rect;
}

void NodeImpl::initNodeSize()
{
    if (!m_shape) {
        return;
    }
    int defaultWidth = 120;
    int defaultHeight = 200;

    for (auto subShape : m_shape->getSubShapes()) {
        if (subShape->getObjectType() == ObjectType::kRectangle) {
            ((Rectangle*)subShape)->setSize(QSize(defaultWidth, defaultHeight));
            return;
        }
    }
    Rectangle* rect = RectangleImpl::New((Shape*)m_shape);
    rect->setWidth(defaultWidth);
    rect->setHeight(defaultHeight);

}

QSize NodeImpl::getSize() const
{
    auto parent = getParent();
    if (!parent) {
        return QSize(0, 0);
    }
    auto parentType = parent->getObjectType();
    if (parentType == ObjectType::kNode) {
        for (auto subShape : m_shape->getSubShapes()) {
            if (subShape->isTypeOf(ObjectType::kRectangle)) {
                return ((Rectangle*)subShape)->getSize();
            }
        }
    }
    return QSize(0, 0);
}

void NodeImpl::setSize(const QSize &size)
{
    auto parent = getParent();
    if (!parent) {
        return;
    }

    auto parentType = parent->getObjectType();
    if (parentType == ObjectType::kNode) {
        for (auto subShape : m_shape->getSubShapes()) {
            if (subShape->getObjectType() == ObjectType::kRectangle) {
                ((Rectangle*)subShape)->setSize(size);
                return;
            }
        }
    }
}

void NodeImpl::addGraphElement(GraphElementImpl *graphElement)
{
    if (graphElement == nullptr) {
        return;
    }
    if (m_elements.contains(graphElement)) {
        return;
    }
    m_elements.append(graphElement);
    graphElement->setParent((Object*)this);
}

void NodeImpl::removeGraphElement(GraphElementImpl *graphElement)
{
    if (graphElement == nullptr) {
        return;
    }
    m_elements.removeAll(graphElement);
    delete graphElement;
}

void NodeImpl::addSubNode(NodeImpl *node)
{
    if (node == nullptr) {
        return;
    }
    if (m_subNodes.contains(node)) {
        return;
    }
    m_subNodes.append(node);
    node->setParent((Object*)this);
}

void NodeImpl::removeSubNode(NodeImpl *node)
{
    if (node == nullptr) {
        return;
    }
    m_subNodes.removeAll(node);
}

void NodeImpl::addInternalPin(PinImpl *pin)
{
    if (pin == nullptr) {
        return;
    }
    if (m_internalPins.contains(pin)) {
        return;
    }
    m_internalPins.append(pin);
    pin->setParent((Object*)this);
}

void NodeImpl::removeInternalPin(PinImpl *pin)
{
    if (pin == nullptr) {
        return;
    }
    m_internalPins.removeAll(pin);
}

void NodeImpl::addBoundaryPin(PinImpl *pin)
{
    if (pin == nullptr) {
        return;
    }
    if (m_boundaryPins.contains(pin)) {
        return;
    }
    m_boundaryPins.append(pin);
    pin->setParent((Object*)this);
}

void NodeImpl::removeBoundaryPin(PinImpl *pin)
{
    if (pin == nullptr) {
        return;
    }
    m_boundaryPins.removeAll(pin);
}

void NodeImpl::addNet(NetImpl *net)
{
    if (net == nullptr) {
        return;
    }
    if (m_nets.contains(net)) {
        return;
    }
    m_nets.append(net);
    net->setParent((Object*)this);
}

void NodeImpl::removeNet(NetImpl *net)
{
    if (net == nullptr) {
        return;
    }
    m_nets.removeAll(net);
}