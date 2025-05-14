//
// Created by 18224 on 2025/5/7.
//

#include "Rectangle.h"
#include "RectangleImpl.h"

using namespace mango::blockdiagram::datamodel;

Rectangle* Rectangle::New(Shape* parent)
{
    return RectangleImpl::New(parent);
}

void Rectangle::setTopLeft(const QPointF& topLeft)
{
    impl_ptr(Rectangle)->setTopLeft(topLeft);
}

QPointF Rectangle::getTopLeft() const
{
    return impl_ptr(Rectangle)->getTopLeft();
}

void Rectangle::setWidth(double width)
{
    impl_ptr(Rectangle)->setWidth(width);
}

double Rectangle::getWidth() const
{
    return impl_ptr(Rectangle)->getWidth();
}

void Rectangle::setHeight(double height)
{
    impl_ptr(Rectangle)->setHeight(height);
}

void Rectangle::setSize(const QSize& size)
{
    impl_ptr(Rectangle)->setSize(size);
}

double Rectangle::getHeight() const
{
    return impl_ptr(Rectangle)->getHeight();
}

QSize Rectangle::getSize() const
{
    return impl_ptr(Rectangle)->getSize();
}