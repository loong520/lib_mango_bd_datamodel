//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObject.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Label;
class Shape;
class Node;

class MANGO_BD_DATAMODEL_API GraphElement : public GObject {
public:
    static GraphElement* New(Node* parent);

    /// 设置形状
    /// \param shape 形状指针
    void setShape(Shape *shape);

    /// 获取形状
    /// \return 形状指针
    Shape *getShape() const;

    /// 添加文本
    /// \param label 文本指针
    void addLabel(Label *label);

    /// 移除文本
    /// \param label 文本指针
    void removeLabel(Label *label);

    /// 获取文本列表
    /// \return 文本列表
    QList<Label*> getLabels() const;

};

}
}
}
