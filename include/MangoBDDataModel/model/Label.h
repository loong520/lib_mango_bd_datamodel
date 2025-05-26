//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GraphElement.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Label;
class GraphElement;

class MANGO_BD_DATAMODEL_API Label : public GraphElement {
public:
    static Label* New(GraphElement* parent);

    /// 克隆对象
    /// \return 克隆的对象指针
    Label* clone() const;

    /// 设置文本
    /// \param text 文本
    void setText(const QString& text);

    /// 获取文本
    /// \return 文本
    QString getText() const;

    /// 设置文本类型
    /// \param type 文本类型
    void setType(LabelType type);

    /// 获取文本类型
    /// \return 文本类型
    LabelType getType() const;

};

}
}
}