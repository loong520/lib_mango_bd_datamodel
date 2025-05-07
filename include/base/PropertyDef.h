//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "Object.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class PropertyDef : public Object {
public:
    /// 增加使用次数
    /// @param number 增加的次数
    void incUseCount(int number);
};

}
}
}
