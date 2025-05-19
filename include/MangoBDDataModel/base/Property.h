//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/base/Object.h"
#include "MangoBDDataModel/base/PropertyDef.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class MANGO_BD_DATAMODEL_API Property : public Object {
public:
    /// 获取属性名称
    /// @return 属性名称
    QString getName() const;

    /// 获取属性定义
    /// @return 属性定义指针
    /// \return
    PropertyDef* getPropertyDef() const;

    /// 获取属性所属对象
    /// @return 属性所属对象指针
    Object* getOwner() const;

    /// 获取属性值的字符串表示
    /// @return 属性值的字符串表示
    QString getValueString() const;
};

}
}
}