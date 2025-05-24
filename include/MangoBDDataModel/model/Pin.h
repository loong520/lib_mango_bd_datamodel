//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GraphElement.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Node;
class LibSymbol;
class Net;

class MANGO_BD_DATAMODEL_API Pin : public GraphElement {
public:
    /// 创建一个新的引脚对象
    /// \param parent 父节点
    /// \param name 引脚名称
    /// \param inBoundary 是否器件引脚(false: 视作模块端口)
    static Pin* New(Node* parent, const QString& name, bool devicePin = true);

    /// 创建一个新的引脚对象
    /// \param parent 父库符号
    /// \param name 引脚名称
    static Pin* New(LibSymbol* parent, const QString& name);

    /// 设置引脚名称
    /// \param name
    void setName(const QString& name);

    /// 获取引脚名称
    /// \return 引脚名称
    QString getName() const;

    /// 添加一个输入的连线
    /// \param net 输入的连线
    void addIncomingNet(Net* net);

    /// 删除一个输入的连线
    /// \param net 输入的连线
    void removeIncomingNet(Net* net);

    /// 获取所有输入的连线
    /// \return 输入的连线列表
    QList<Net*> getIncomingNets() const;

    /// 添加一个输出的连线
    /// \param net 输出的连线
    void addOutgoingNet(Net* net);

    /// 删除一个输出的连线
    /// \param net 输出的连线
    void removeOutgoingNet(Net* net);

    /// 获取所有输出的连线
    /// \return 输出的连线列表
    QList<Net*> getOutgoingNets() const;

    /// 设置引脚形状类型
    /// \param shapeType 形状类型
    void setShapeType(PinShape shapeType);

    /// 获取引脚形状类型
    /// \return 形状类型
    PinShape getShapeType() const;

    /// 设置引脚方向
    /// \param direction 方向
    void setDirection(Direction direction);

    /// 获取引脚方向
    /// \return 方向
    Direction getDirection() const;
};

}
}
}