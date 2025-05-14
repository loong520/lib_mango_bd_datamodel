//
// Created by 18224 on 2025/5/7.
//

#include "GraphElement.h"
#include "GraphElementImpl.h"
#include "LabelImpl.h"

using namespace mango::blockdiagram::datamodel;

GraphElement* GraphElement::New(Node* parent)
{
    return GraphElementImpl::New(parent);
}

void GraphElement::setShape(Shape *shape)
{
    impl_ptr(GraphElement)->setShape((ShapeImpl*)shape);
}

Shape *GraphElement::getShape() const
{
    return (Shape*)impl_ptr(GraphElement)->getShape();
}

void GraphElement::addLabel(Label *label)
{
    impl_ptr(GraphElement)->addLabel((LabelImpl*)label);
}

void GraphElement::removeLabel(Label *label)
{
    impl_ptr(GraphElement)->removeLabel((LabelImpl*)label);
}

QList<Label*> GraphElement::getLabels() const
{
    QList<Label*> labels;
    for (auto label : impl_ptr(GraphElement)->getLabels()) {
        labels.append((Label*)label);
    }
    return labels;
}