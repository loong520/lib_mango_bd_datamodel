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