//
// Created by 18224 on 2025/5/7.
//

#include "PropertyDef.h"
#include "impl/PropertyDefImpl.h"

using namespace mango::blockdiagram::datamodel;

void PropertyDef::incUseCount(int number)
{
    impl_ptr(PropertyDef)->incUseCount(number);
}