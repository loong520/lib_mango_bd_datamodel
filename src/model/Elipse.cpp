//
// Created by 18224 on 2025/5/7.
//

#include "Elipse.h"
#include "ElipseImpl.h"

using namespace mango::blockdiagram::datamodel;

Elipse* Elipse::New(Shape* parent)
{
    return ElipseImpl::New(parent);
}