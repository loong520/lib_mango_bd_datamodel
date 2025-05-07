//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "ObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {


class PropertyDefImpl : public ObjectImpl {
public:
    void incUseCount(int number);
};

}
}
}