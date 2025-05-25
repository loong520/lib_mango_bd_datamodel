//
// Created by Administrator on 2025/5/25.
//
#pragma once

#include "MangoBDDataModel/base/ObjectType.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class MANGO_BD_DATAMODEL_API Util
{
public:
    static void *memAlloc(size_t len);
    static void memFree(void *ptr);
};

}
}
}

