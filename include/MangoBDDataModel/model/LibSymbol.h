//
// Created by 18224 on 2025/5/23.
//
#pragma once

#include "MangoBDDataModel/model/GraphElement.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Pin;

class MANGO_BD_DATAMODEL_API LibSymbol : public GraphElement {
public:
    static LibSymbol *New(Node *parent);

    /// 克隆对象
    /// \return 克隆的对象指针
    LibSymbol *clone() const;

    /// 添加一个引脚
    /// \param pin 引脚对象
    void addPin(Pin* pin);

    /// 移除一个引脚
    /// \param pin 引脚对象
    void removePin(Pin* pin);

    /// 获取所有引脚
    /// \return 所有引脚列表
    QList<Pin*> getPins() const;
};

}
}
}
