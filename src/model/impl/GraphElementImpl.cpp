//
// Created by 18224 on 2025/5/7.
//

#include "GraphElementImpl.h"
#include "NodeImpl.h"
#include "LabelImpl.h"
#include "ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

GraphElement* GraphElementImpl::New(Node* parent)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    GraphElementImpl* impl = new GraphElementImpl((Object*)parent);
    obj_impl_ptr(Node, parent)->addGraphElement((GraphElementImpl*)impl);
    return (GraphElement*)impl;
}

GraphElementImpl::GraphElementImpl(Object* parent) : GObjectImpl(parent)
{
    m_shape = (ShapeImpl*)ShapeImpl::New((GraphElement*)this);
}

bool GraphElementImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kGraphElement) {
        return true;
    }
    return false;
}

void GraphElementImpl::Delete()
{
    if (!m_parent) {
        // TODO: LOG_ERROR
        return;
    }

    ObjectType::TypeId typeId = m_parent->getObjectType();
    if (typeId == ObjectType::kNode) {
        obj_impl_ptr(Node, m_parent)->removeGraphElement((GraphElementImpl*)this);
    } else {
        // TODO: LOG_ERROR
        return;
    }
}

QRectF GraphElementImpl::getBoundingRect() const
{
    QRectF rect;
    if (m_shape) {
        auto shapeRect = m_shape->getBoundingRect();
        shapeRect = m_transform.mapRect(shapeRect);
        rect |= shapeRect;
    }
    for (auto label : m_labels) {
        auto labelRect = label->getBoundingRect();
        labelRect = m_transform.mapRect(labelRect);
        rect |= labelRect;
    }
    return rect;
}

bool GraphElementImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool GraphElementImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

void GraphElementImpl::setName(const QString& name)
{
    for (auto label : m_labels) {
        if (label->getType() == LabelType::LabelForMainName) {
            label->setText(name);
            return;
        }
    }

    // create a new label for main name
    LabelImpl* label = (LabelImpl*)LabelImpl::New((GraphElement*)this);
    label->setType(LabelType::LabelForMainName);
    label->setText(name);

    addLabel((LabelImpl*)label);
}

QString GraphElementImpl::getName() const
{
    for (auto label : m_labels) {
        if (label->getType() == LabelType::LabelForMainName) {
            return label->getText();
        }
    }
    return QString();
}

void GraphElementImpl::setShape(ShapeImpl *shape)
{
    if (shape == nullptr) {
        return;
    }
    if (shape == m_shape) {
        return;
    }

    if (m_shape) {
        ShapeImpl * oldShape = m_shape;
        m_shape = shape;
        oldShape->Delete();
    } else {
        m_shape = shape;
    }
}

ShapeImpl *GraphElementImpl::getShape() const
{
    return m_shape;
}

void GraphElementImpl::addLabel(LabelImpl *label)
{
    if (label == nullptr) {
        return;
    }

    if (m_labels.contains(label)) {
        return;
    }
    m_labels.append(label);
    label->setParent((Object*)this);
}

void GraphElementImpl::removeLabel(LabelImpl *label)
{
    if (label == nullptr) {
        return;
    }
    m_labels.removeAll(label);
}

QList<LabelImpl*> GraphElementImpl::getLabels() const
{
    return m_labels;
}

LabelImpl* GraphElementImpl::findMainName(const GraphElementImpl* element)
{
    for(auto lab : element->getLabels()) {
        if (lab->getType() == LabelType::LabelForMainName) {
            return lab;
        }
    }
    return nullptr;
}