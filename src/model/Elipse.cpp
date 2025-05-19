//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Elipse.h"
#include "impl/ElipseImpl.h"

using namespace mango::blockdiagram::datamodel;

Elipse* Elipse::New(Shape* parent)
{
    return ElipseImpl::New(parent);
}

void Elipse::setCenter(const QPointF& center)
{
    obj_impl_ptr(Elipse, this)->setCenter(center);
}

QPointF Elipse::getCenter() const
{
    return obj_impl_ptr(Elipse, this)->getCenter();
}

void Elipse::setRadiusX(double radiusX)
{
    obj_impl_ptr(Elipse, this)->setRadiusX(radiusX);
}

double Elipse::getRadiusX() const
{
    return obj_impl_ptr(Elipse, this)->getRadiusX();
}

void Elipse::setRadiusY(double radiusY)
{
    obj_impl_ptr(Elipse, this)->setRadiusY(radiusY);
}

double Elipse::getRadiusY() const
{
    return obj_impl_ptr(Elipse, this)->getRadiusY();
}