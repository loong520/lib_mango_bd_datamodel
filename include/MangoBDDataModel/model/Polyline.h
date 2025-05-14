//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObject.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Shape;

class MANGO_BD_DATAMODEL_API Polyline : public GObject {
public:

    /// 创建一个新的折线对象
    /// \param parent 父对象
    /// \return 折线对象指针
    static Polyline* New(Shape* parent);

};

}
}
}
