//
// Created by 18224 on 2025/5/7.
//

#include "Polygon.h"
#include "PolygonImpl.h"

using namespace mango::blockdiagram::datamodel;

Polygon* Polygon::New(Shape* parent)
{
    return PolygonImpl::New(parent);
}