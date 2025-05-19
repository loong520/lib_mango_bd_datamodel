//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Polygon.h"
#include "impl/PolygonImpl.h"

using namespace mango::blockdiagram::datamodel;

Polygon* Polygon::New(Shape* parent)
{
    return PolygonImpl::New(parent);
}