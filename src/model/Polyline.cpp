//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Polyline.h"
#include "impl/PolylineImpl.h"

using namespace mango::blockdiagram::datamodel;

Polyline* Polyline::New(Shape* parent)
{
    return PolylineImpl::New(parent);
}

Polyline* Polyline::New(Shape* parent, const QList<QPointF> &v)
{
    return PolylineImpl::New(parent, v);
}

int Polyline::size() const
{
    return impl_ptr(Polyline)->size();
}

bool Polyline::isEmpty() const
{
    return impl_ptr(Polyline)->isEmpty();
}

QPointF& Polyline::first()
{
    return impl_ptr(Polyline)->first();
}

const QPointF& Polyline::constFirst() const
{
    return impl_ptr(Polyline)->constFirst();
}

QPointF& Polyline::last()
{
    return impl_ptr(Polyline)->last();
}

const QPointF& Polyline::constLast() const
{
    return impl_ptr(Polyline)->constLast();
}

const QPointF& Polyline::get(int i) const
{
    return impl_ptr(Polyline)->get(i);
}

void Polyline::append(const QPointF &p)
{
    impl_ptr(Polyline)->append(p);
}

void Polyline::append(const QList<QPointF> &points)
{
    impl_ptr(Polyline)->append(points);
}

void Polyline::prepend(const QPointF &p)
{
    impl_ptr(Polyline)->prepend(p);
}

void Polyline::replace(int index, const QPointF &p)
{
    impl_ptr(Polyline)->replace(index, p);
}

void Polyline::removeAt(int i)
{
    impl_ptr(Polyline)->removeAt(i);
}

void Polyline::removeFirst()
{
    impl_ptr(Polyline)->removeFirst();
}

void Polyline::removeLast()
{
    impl_ptr(Polyline)->removeLast();
}

void Polyline::clear()
{
    impl_ptr(Polyline)->clear();
}