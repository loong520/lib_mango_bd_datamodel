//
// Created by 18224 on 2025/5/26.
//
#pragma once

#include "MangoBDDataModel/base/Config.h"
#include <QString>

namespace mango {
namespace blockdiagram {
namespace datamodel {

class MANGO_BD_DATAMODEL_API LayeredOptions {
public:
    /// 获取单例
    /// \return 单例
    static LayeredOptions &instance();

    /// 是否为图元指定单独的间距，与父对象的值不同
    /// \return 是否未图元指定单独的间距
    bool getSpacingIndividual() const;

    /// 展开层的分割
    /// \return 展开层的分割
    /// \note true则代表展示到下一层
    bool getUnzippingLayerSplit() const;

    /// 布线策略(1: 正交布线)
    /// \return 布线策略
    quint32 getRoutingOption() const;

    /// 布局方向(1: ↑, 2: →, 3: ↓, 4: ←)
    /// \return 布局方向
    quint32 getLayoutDirection() const;

    /// 节点内部自环是否激活
    /// \return 是否激活
    bool getInsideSelfLoops() const;

    /// 文本和它关联的文本框之间的间距
    /// \return 间距
    quint32 getTextAndNode() const;

    /// 同一节点关联的文本框之间的间距
    /// \return 间距
    quint32 getTextAndText() const;

    /// 组件之间的间距
    /// \return 间距
    quint32 getComponentAndComponent() const;

    /// 边与边之间的水平间距
    /// \return 间距
    quint32 getEdgeAndEdgeH() const;

    /// 边与边之间的垂直间距
    /// \return 间距
    quint32 getEdgeAndEdgeV() const;

    /// 边与边之间的整体间距
    /// \return 间距
    quint32 getEdgeAndEdge() const;

    /// 边的标签与其关联的边之间的间距
    /// \return 间距
    quint32 getEdgeAndLabel() const;

    /// 边和节点之间的水平间距
    /// \return 间距
    quint32 getEdgeAndNodeH() const;

    /// 边和节点之间的垂直间距
    /// \return 间距
    quint32 getEdgeAndNodeV() const;

    /// 同一图形元素上的标签和标签之间的间距
    /// \return 间距
    quint32 getLabelAndLabel() const;

    /// 标签和其表征的端口之间的水平间距
    /// \return 间距
    quint32 getLabelAndPortH() const;

    /// 标签和其表征的端口之间的垂直间距
    /// \return 间距
    quint32 getLabelAndPortV() const;

    /// 标签和其关联的节点的边框之间的间距
    /// \return 间距
    quint32 getNodeAndLabel() const;

    /// 节点和节点之间的水平间距
    /// \return 间距
    quint32 getNodeAndNodeH() const;

    /// 节点和节点之间的垂直间距
    /// \return 间距
    quint32 getNodeAndNodeV() const;

    /// 节点和其自身循环边之间应该保留的间距
    /// \return 间距
    quint32 getNodeSelfLoop() const;

    /// 同一节点的成对端口之间的间距
    /// \return 间距
    quint32 getPortAndPort() const;

    /// 符号和符号之间的间距
    /// \return 间距
    quint32 getSymbolAndSymbol() const;  
    
    /// 位置最上的子节点和父节点的内边距
    /// \return 间距
    quint32 getPaddingTop() const;
    
    /// 位置最下的子节点和父节点的内边距
    /// \return 间距
    quint32 getPaddingBottom() const;
    
    /// 位置最左的子节点和父节点的内边距
    /// \return 间距
    quint32 getPaddingLeft() const;
    
    /// 位置最右的子节点和父节点的内边距
    /// \return 间距
    quint32 getPaddingRight() const;
    
    /// 端口上方的额外空间
    /// \return 间距
    quint32 getAdditionalPortSpaceTop() const;
    
    /// 端口下方的额外空间
    /// \return 间距
    quint32 getAdditionalPortSpaceBottom() const;
    
    /// 端口左侧的额外空间
    /// \return 间距
    quint32 getAdditionalPortSpaceLeft() const;
    
    /// 端口右侧的额外空间
    /// \return 间距
    quint32 getAdditionalPortSpaceRight() const;


    // 禁用构造和赋值运算符
    LayeredOptions() = delete;
    LayeredOptions(const LayeredOptions&) = delete;
    ~LayeredOptions() = delete;
    LayeredOptions& operator=(const LayeredOptions&) = delete;
};

}
}
}