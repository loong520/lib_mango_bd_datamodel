//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElement.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Node;
class Symbol;

class MANGO_BD_DATAMODEL_API Pin : public GraphElement {
public:
    /// 创建一个新的引脚对象
    /// \param parent 父节点
    /// \param name 引脚名称
    /// \param inBoundary 是否在边界上
    static Pin* New(Node* parent, const QString& name, bool inBoundary);

    /// 创建一个新的引脚对象
    /// \param parent 父symbol
    /// \param name 引脚名称
    static Pin* New(Symbol* parent, const QString& name);

    /// 设置引脚名称
    /// \param name
    void setName(const QString& name);

    /// 获取引脚名称
    /// \return 引脚名称
    QString getName() const;


};

}
}
}