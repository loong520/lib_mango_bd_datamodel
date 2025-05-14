//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObject.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Shape;

class MANGO_BD_DATAMODEL_API Elipse : public GObject {
public:
    /// 创建一个新的椭圆对象
    /// \param parent 父对象
    /// \return
    static Elipse* New(Shape* parent);

};

}
}
}