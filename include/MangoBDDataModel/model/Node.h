//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GraphElement.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Pin;
class Net;

class MANGO_BD_DATAMODEL_API Node : public GraphElement {
public:
    /// 创建一个新的节点对象
    /// \param parent 父节点
    /// \param isHierarchical 是否为层次节点
    /// \param isRoot 是否为根节点
    /// \return 新建节点对象
    /// \note parent为空视为root节点，不会有shape
    static Node* New(Node* parent, bool isHierarchical = false, bool isRoot = false);

    /// 克隆对象
    /// \return 克隆的对象指针
    Node* clone() const;

    /// 节点大小
    /// \return 大小
    QSizeF getSize() const;

    /// 设置节点大小
    /// \param size 大小
    /// \note root节点调用该函数无效
    void setSize(const QSizeF &size);

    /// 是否为根节点
    /// \return 是否为根节点
    bool isRootNode() const;

    /// 是否为层次节点
    /// \return 是否为层次节点
    bool isHierarchical() const;

    /// 增加子图元
    /// \param graphElement 子图元
    void addGraphElement(GraphElement *graphElement);

    /// 删除子图元
    /// \param graphElement 子图元
    void removeGraphElement(GraphElement *graphElement);

    /// 获取全部子图元
    /// \return 子图元列表
    QList<GraphElement*> getGraphElements() const;

    /// 获取指定类型子图元
    /// \param type 子图元类型
    /// \return 子图元列表
    QList<GraphElement*> getGraphElements(ObjectType type) const;

    /// 增加子节点
    /// \param node 子节点
    void addSubNode(Node *node);

    /// 删除子节点
    /// \param node 子节点
    void removeSubNode(Node *node);

    /// 获取子节点
    /// \return 子节点列表
    QList<Node*> getSubNodes() const;

    /// 增加独立引脚
    /// \param pin 独立引脚
    void addIndependentPin(Pin *pin);

    /// 删除独立引脚
    /// \param pin 独立引脚
    void removeIndependentPin(Pin *pin);

    /// 获取独立的引脚
    /// \return 内部引脚列表
    QList<Pin*> getIndependentPin() const;

    /// 增加器件引脚
    /// \param pin 器件引脚
    void addDevicePin(Pin *pin);

    /// 删除器件引脚
    /// \param pin 器件引脚
    void removeDevicePin(Pin *pin);

    /// 获取器件引脚
    /// \return 器件引脚列表
    QList<Pin*> getDevicePins() const;

    /// 增加网络
    /// \param net 网络
    void addNet(Net *net);

    /// 删除网络
    /// \param net 网络
    void removeNet(Net *net);

    /// 获取网络
    /// \return 网络列表
    QList<Net*> getNets() const;

    /// 获取指定位置的子图元
    /// \param pos 位置坐标
    /// \return 子图元列表（Z值降序排列）
    QList<GObject *> items(const QPointF &pos) const;

    /// 获取指定区域内的子图元
    /// \param rect 区域
    /// \return 子图元列表（Z值降序排列）
    QList<GObject *> items(const QRectF &rect) const;
};

}
}
}