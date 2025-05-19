//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GObject.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Shape;

class MANGO_BD_DATAMODEL_API Polygon : public GObject {
public:
    /// 创建一个新的多边形对象
    /// \param parent 父对象
    /// \return
    static Polygon* New(Shape* parent);


};

}
}
}
