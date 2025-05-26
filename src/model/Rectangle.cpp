//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Rectangle.h"
#include "impl/RectangleImpl.h"

using namespace mango::blockdiagram::datamodel;

Rectangle* Rectangle::New(Shape* parent)
{
    return (Rectangle*)RectangleImpl::New((ShapeImpl*)parent);
}

Rectangle* Rectangle::New(Shape* parent, const QRectF &rect)
{
    return (Rectangle*)RectangleImpl::New((ShapeImpl*)parent, rect);
}

Rectangle* Rectangle::clone() const
{
    return (Rectangle*)impl_ptr(Rectangle)->clone();
}

void Rectangle::setRect(const QRectF &rect)
{
    impl_ptr(Rectangle)->setRect(rect);
}

QRectF Rectangle::getRect() const
{
    return impl_ptr(Rectangle)->getRect();
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

void Rectangle::setSize(const QSizeF& size)
{
    impl_ptr(Rectangle)->setSize(size);
}

double Rectangle::getHeight() const
{
    return impl_ptr(Rectangle)->getHeight();
}

QSizeF Rectangle::getSize() const
{
    return impl_ptr(Rectangle)->getSize();
}