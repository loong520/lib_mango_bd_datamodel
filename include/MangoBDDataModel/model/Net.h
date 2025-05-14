//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElement.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Node;
class Pin;

class MANGO_BD_DATAMODEL_API Net : public GraphElement {
public:
    /// 创建一个新的连线对象
    /// \param parent 父节点
    /// \return 新建连线对象
    static Net* New(Node* parent);

    /// 增加源引脚
    /// \param pin 源引脚
    void addSource(Pin* pin);

    /// 删除源引脚
    /// \param pin 源引脚
    void removeSource(Pin* pin);

    /// 获取源引脚
    /// \return 源引脚列表
    QList<Pin*> getSources() const;

    /// 增加目标引脚
    /// \param pin 目标引脚
    void addTarget(Pin* pin);

    /// 删除目标引脚
    /// \param pin 目标引脚
    void removeTarget(Pin* pin);

    /// 获取目标引脚
    /// \return 目标引脚列表
    QList<Pin*> getTargets() const;

    /// 设置连线模式
    /// \param mode 连线模式
    void setConnectMode(ConnectMode mode);

    /// 获取连线模式
    /// \return 连线模式
    ConnectMode getConnectMode() const;

    /// 获取线宽
    /// \return 线宽
    int getLineWidth() const;

    /// 获取线颜色
    /// \return 线颜色
    QString getLineColor() const;
};

}
}
}