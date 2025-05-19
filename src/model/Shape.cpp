//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Shape.h"
#include "impl/ShapeImpl.h"

using namespace mango::blockdiagram::datamodel;

Shape *Shape::New(GraphElement *parent)
{
    return ShapeImpl::New(parent);
}

void Shape::addSubShape(GObject *shape)
{
    impl_ptr(Shape)->addSubShape((GObjectImpl*)shape);
}

void Shape::removeSubShape(GObject *shape)
{
    impl_ptr(Shape)->removeSubShape((GObjectImpl*)shape);
}

QList<GObject *> Shape::getSubShapes() const
{
    QList<GObject*> subShapes;
    for (auto shape : impl_ptr(Shape)->getSubShapes()) {
        subShapes.append((GObject*)shape);
    }
    return subShapes;
}

bool Shape::isEmpty() const
{
    return impl_ptr(Shape)->isEmpty();
}