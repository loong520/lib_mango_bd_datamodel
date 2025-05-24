//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GraphElement.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class LibSymbol;
class Pin;

class MANGO_BD_DATAMODEL_API Symbol : public GraphElement {
public:
    static Symbol *New(Node *parent, LibSymbol *libSymbol);

    /// 设置库符号
    /// \param aLibSymbol 库符号对象指针
    /// \note 引脚列表将相应更新, 库符号对象可以为 null, 以清除库符号链接以及引脚映射
    void setLibSymbol(LibSymbol *aLibSymbol);

    /// 获取库符号
    /// \return 库符号对象指针
    LibSymbol *getLibSymbol() const;

    /// 获取所有引脚
    /// \return 所有引脚列表
    QList<Pin*> getPins() const;

    /// 更新每个引脚的 PIN 对象缓存
    void updatePins();
};

}
}
}