//
// Created by Administrator on 2025/5/25.
//

#include "include/MangoBDDataModel/util/Util.h"

using namespace mango::blockdiagram::datamodel;

void* Util::memAlloc(size_t size)
{
    void *addr = malloc(size);
    memset(addr, 0, size);
    return addr;
}

void Util::memFree(void *ptr)
{
    if (ptr) {
        free(ptr);
    }
}