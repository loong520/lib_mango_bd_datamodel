//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Arc.h"
#include "impl/ArcImpl.h"

using namespace mango::blockdiagram::datamodel;

Arc* Arc::New(Shape* parent)
{
    return ArcImpl::New(parent);
}

Arc* Arc::New(Shape* parent, double radius, const QPointF& center, double startAngle, double spanAngle)
{
    return ArcImpl::New(parent, radius, center, startAngle, spanAngle);
}

void Arc::setCenter(const QPointF center)
{
    impl_ptr(Arc)->setCenter(center);
}

QPointF Arc::getCenter() const
{
    return impl_ptr(Arc)->getCenter();
}

void Arc::setRadius(double radius)
{
    impl_ptr(Arc)->setRadius(radius);
}

double Arc::getRadius() const
{
    return impl_ptr(Arc)->getRadius();
}

void Arc::setStartAngle(double startAngle)
{
    impl_ptr(Arc)->setStartAngle(startAngle);
}

double Arc::getStartAngle() const
{
    return impl_ptr(Arc)->getStartAngle();
}

void Arc::setSpanAngle(double spanAngle)
{
    impl_ptr(Arc)->setSpanAngle(spanAngle);
}

double Arc::getSpanAngle() const
{
    return impl_ptr(Arc)->getSpanAngle();
}