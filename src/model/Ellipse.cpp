//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Ellipse.h"
#include "impl/EllipseImpl.h"

using namespace mango::blockdiagram::datamodel;

Ellipse* Ellipse::New(Shape* parent)
{
    return (Ellipse*)EllipseImpl::New((ShapeImpl*)parent);
}

Ellipse* Ellipse::New(Shape* parent, double radiusX, double radiusY, const QPointF& center)
{
    return (Ellipse*)EllipseImpl::New((ShapeImpl*)parent, radiusX, radiusY, center);
}

Ellipse* Ellipse::clone() const
{
    return (Ellipse*)obj_impl_ptr(Ellipse, this)->clone();
}

void Ellipse::setCenter(const QPointF& center)
{
    obj_impl_ptr(Ellipse, this)->setCenter(center);
}

QPointF Ellipse::getCenter() const
{
    return obj_impl_ptr(Ellipse, this)->getCenter();
}

void Ellipse::setRadiusX(double radiusX)
{
    obj_impl_ptr(Ellipse, this)->setRadiusX(radiusX);
}

double Ellipse::getRadiusX() const
{
    return obj_impl_ptr(Ellipse, this)->getRadiusX();
}

void Ellipse::setRadiusY(double radiusY)
{
    obj_impl_ptr(Ellipse, this)->setRadiusY(radiusY);
}

double Ellipse::getRadiusY() const
{
    return obj_impl_ptr(Ellipse, this)->getRadiusY();
}