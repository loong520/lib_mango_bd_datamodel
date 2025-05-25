//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Polygon.h"
#include "impl/PolygonImpl.h"

using namespace mango::blockdiagram::datamodel;

Polygon* Polygon::New(Shape* parent)
{
    return (Polygon*)PolygonImpl::New((ShapeImpl*)parent);
}

Polygon* Polygon::New(Shape* parent, const QList<QPointF> &v)
{
    return (Polygon*)PolygonImpl::New((ShapeImpl*)parent, v);
}

QPolygonF Polygon::toQPolygon() const
{
    return impl_ptr(Polygon)->toQPolygon();
}

int Polygon::size() const
{
    return impl_ptr(Polygon)->size();
}

bool Polygon::isEmpty() const
{
    return impl_ptr(Polygon)->isEmpty();
}

QPointF& Polygon::first()
{
    return impl_ptr(Polygon)->first();
}

const QPointF& Polygon::constFirst() const
{
    return impl_ptr(Polygon)->constFirst();
}

QPointF& Polygon::last()
{
    return impl_ptr(Polygon)->last();
}

const QPointF& Polygon::constLast() const
{
    return impl_ptr(Polygon)->constLast();
}

const QPointF& Polygon::get(int i) const
{
    return impl_ptr(Polygon)->get(i);
}

void Polygon::append(const QPointF &p)
{
    impl_ptr(Polygon)->append(p);
}

void Polygon::append(const QList<QPointF> &points)
{
    impl_ptr(Polygon)->append(points);
}

void Polygon::prepend(const QPointF &p)
{
    impl_ptr(Polygon)->prepend(p);
}

void Polygon::replace(int index, const QPointF &p)
{
    impl_ptr(Polygon)->replace(index, p);
}

void Polygon::removeAt(int i)
{
    impl_ptr(Polygon)->removeAt(i);
}

void Polygon::removeFirst()
{
    impl_ptr(Polygon)->removeFirst();
}

void Polygon::removeLast()
{
    impl_ptr(Polygon)->removeLast();
}

void Polygon::clear()
{
    impl_ptr(Polygon)->clear();
}


