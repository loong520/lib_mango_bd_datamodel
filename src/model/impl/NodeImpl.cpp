//
// Created by 18224 on 2025/5/7.
//

#include "NodeImpl.h"
#include "ShapeImpl.h"
#include "RectangleImpl.h"
#include "PinImpl.h"
#include "NetImpl.h"

using namespace mango::blockdiagram::datamodel;

Node* NodeImpl::New(Node *parent)
{
    NodeImpl* impl = new NodeImpl((Object*)parent);
    if (parent) {
        impl->initNodeSize();
        obj_impl_ptr(Node, parent)->addSubNode(impl);
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
        for (auto element : m_allElements) {
            auto elementRect = element->getBoundingRect();
            rect = rect.united(elementRect);
        }
        for (auto pin : m_independentPins) {
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
        for (auto pin : m_devicePins) {
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
            ((RectangleImpl*)subShape)->setSize(QSize(defaultWidth, defaultHeight));
            return;
        }
    }
    RectangleImpl* rect = (RectangleImpl*)RectangleImpl::New((Shape*)m_shape);
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
                return ((RectangleImpl*)subShape)->getSize();
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
                ((RectangleImpl*)subShape)->setSize(size);
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

    // 加入所有子图元列表
    if (m_allElements.contains(graphElement)) {
        return;
    }
    m_allElements.append(graphElement);
    graphElement->setParent((Object*)this);

    // 按类型加入不同的列表
    if (graphElement->getObjectType() == ObjectType::kNode) {
        addSubNode((NodeImpl*)graphElement);
        return;
    } else if (graphElement->getObjectType() == ObjectType::kPin) {
        addIndependentPin((PinImpl*)graphElement);
        return;
    } else if (graphElement->getObjectType() == ObjectType::kNet) {
        addNet((NetImpl*)graphElement);
        return;
    }

    // 加入索引树
    // todo: implement
}

void NodeImpl::removeGraphElement(GraphElementImpl *graphElement)
{
    if (graphElement == nullptr) {
        return;
    }
    if (graphElement->getObjectType() == ObjectType::kNode) {
        removeSubNode((NodeImpl*)graphElement);
        return;
    } else if (graphElement->getObjectType() == ObjectType::kPin) {
        removeIndependentPin((PinImpl*)graphElement);
        return;
    } else if (graphElement->getObjectType() == ObjectType::kNet) {
        removeNet((NetImpl*)graphElement);
        return;
    }

    // 从索引树中删除
    // todo: implement

    m_allElements.removeAll(graphElement);
    delete graphElement;
}

QList<GraphElementImpl*> NodeImpl::getGraphElements() const
{
    return m_allElements;
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

void NodeImpl::addIndependentPin(PinImpl *pin)
{
    if (pin == nullptr) {
        return;
    }
    if (m_independentPins.contains(pin)) {
        return;
    }
    m_independentPins.append(pin);
    pin->setParent((Object*)this);
}

void NodeImpl::removeIndependentPin(PinImpl *pin)
{
    if (pin == nullptr) {
        return;
    }
    m_independentPins.removeAll(pin);
}

void NodeImpl::addDevicePin(PinImpl *pin)
{
    if (pin == nullptr) {
        return;
    }
    if (m_devicePins.contains(pin)) {
        return;
    }
    m_devicePins.append(pin);
    pin->setParent((Object*)this);
}

void NodeImpl::removeDevicePin(PinImpl *pin)
{
    if (pin == nullptr) {
        return;
    }
    m_devicePins.removeAll(pin);
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

QList<GObjectImpl *> NodeImpl::items(const QPointF &pos) const
{
    QList<GObjectImpl *> items;
    return items;
}

QList<GObjectImpl *> NodeImpl::items(const QRectF &rect) const
{
    QList<GObjectImpl *> items;
    return items;
}