//
// Created by 18224 on 2025/5/7.
//

#include "NodeImpl.h"
#include "ShapeImpl.h"
#include "RectangleImpl.h"
#include "PinImpl.h"
#include "NetImpl.h"

using namespace mango::blockdiagram::datamodel;

Node* NodeImpl::New(Node *parent, bool isHierarchical, bool isRoot)
{
    NodeImpl* impl = new NodeImpl((Object*)parent, isHierarchical, isRoot);
    if (parent) {
        obj_impl_ptr(Node, parent)->addSubNode(impl);
    }
    return (Node*)impl;
}

NodeImpl::NodeImpl(Object* parent, bool isHierarchical, bool isRoot)
    : GraphElementImpl(parent), m_isHierarchical(isHierarchical), m_isRoot(isRoot)
{
    if (m_shape) {
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
        for (auto GObject : m_rtree) {
            auto GObjectRect = GObject->getBoundingRect();
            rect |= GObjectRect;
        }
    } else {
        // 非根节点的边界矩形为节点边界矩形和节点上pin边界矩形的并集
        if (m_shape) {
            auto shapeRect = m_shape->getBoundingRect();
            rect |= shapeRect;
        }
        for (auto pin : m_devicePins) {
            auto pinRect = pin->getBoundingRect();
            rect |= pinRect;
        }
    }
    return rect;
}

bool NodeImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool NodeImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

QSizeF NodeImpl::getSize() const
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

void NodeImpl::setSize(const QSizeF &size)
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

void NodeImpl::addGraphElement(GObjectImpl *element)
{
    if (element == nullptr) {
        return;
    }
    if (m_rtree.contains((GObject*)element, true)) {
        return;
    }
    // 加入索引树
    m_rtree.insert((GObject*)element);

    // 按类型加入不同的列表
    if (element->getObjectType() == ObjectType::kNode) {
        auto node = (NodeImpl*)element;
        if (m_subNodes.contains(node)) {
            return;
        }
        m_subNodes.append(node);
    } else if (element->getObjectType() == ObjectType::kPin) {
        auto pin = (PinImpl*)element;
        if (pin->m_isDevicePin) {
            m_devicePins.append(pin);
        } else {
            m_independentPins.append(pin);
        }
    } else if (element->getObjectType() == ObjectType::kNet) {
        auto net = (NetImpl*)element;
        if (m_nets.contains(net)) {
            return;
        }
        m_nets.append(net);
    }
    // 设置父节点
    element->setParent((Object*)this);
}

void NodeImpl::removeGraphElement(GObjectImpl *element)
{
    if (element == nullptr) {
        return;
    }

    // 从索引树中删除
    m_rtree.remove((GObject*)element);

    // 从类型列表删除
    if (element->getObjectType() == ObjectType::kNode) {
        m_subNodes.removeAll((NodeImpl*)element);
    }
    else if (element->getObjectType() == ObjectType::kPin) {
        if (((PinImpl*)element)->m_isDevicePin) {
            m_devicePins.removeAll((PinImpl*)element);
        } else {
            m_independentPins.removeAll((PinImpl*)element);
        }
    }
    else if (element->getObjectType() == ObjectType::kNet) {
        m_nets.removeAll((NetImpl*)element);
    }

    // 清理内存
    element->Delete();
}

QList<GObjectImpl*> NodeImpl::getGraphElements() const
{
    QList<GObjectImpl*> elements;
    elements.reserve(m_rtree.size());

    for (auto element : m_rtree) {
        elements.push_back((GObjectImpl*)element);
    }
    return elements;
}

void NodeImpl::addSubNode(NodeImpl *node)
{
    addGraphElement((GObjectImpl*)node);
}

void NodeImpl::removeSubNode(NodeImpl *node)
{
    removeGraphElement((GObjectImpl*)node);
}

void NodeImpl::addIndependentPin(PinImpl *pin)
{
    addGraphElement((GObjectImpl*)pin);
}

void NodeImpl::removeIndependentPin(PinImpl *pin)
{
    removeGraphElement((GObjectImpl*)pin);
}

void NodeImpl::addDevicePin(PinImpl *pin)
{
    addGraphElement((GObjectImpl*)pin);
}

void NodeImpl::removeDevicePin(PinImpl *pin)
{
    removeGraphElement((GObjectImpl*)pin);
}

void NodeImpl::addNet(NetImpl *net)
{
    addGraphElement((GObjectImpl*)net);
}

void NodeImpl::removeNet(NetImpl *net)
{
    removeGraphElement((GObjectImpl*)net);
}

QList<GObjectImpl *> NodeImpl::items(const QPointF &pos) const
{
    QList<GObjectImpl *> objects;

    QRectF rect(pos.x(), pos.y(), 1, 1);
    for (auto item : m_rtree.overlapping(rect)) {
        if (item->hitTest(pos)) {
            objects.push_back((GObjectImpl*)item);
        }
    }
    return objects;
}

QList<GObjectImpl *> NodeImpl::items(const QRectF &rect) const
{
    QList<GObjectImpl *> objects;

    for (auto item : m_rtree.overlapping(rect)) {
        if (item->hitTest(rect, false)) {
            objects.push_back((GObjectImpl*)item);
        }
    }
    return objects;
}