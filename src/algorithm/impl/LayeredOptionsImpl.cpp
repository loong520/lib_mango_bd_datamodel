//
// Created by 18224 on 2025/5/26.
//

#include "LayeredOptionsImpl.h"
#include <QFile>
#include <QSettings>
#include <iostream>

using namespace mango::blockdiagram::datamodel;

LayeredOptionsImpl &LayeredOptionsImpl::instance()
{
    static LayeredOptionsImpl impl;
    return impl;
}

bool LayeredOptionsImpl::getSpacingIndividual() const
{
    return m_settings[LayoutOptionsGroup][SpacingIndividual].toBool();
}

bool LayeredOptionsImpl::getUnzippingLayerSplit() const
{
    return m_settings[LayoutOptionsGroup][UnzippingLayerSplit].toBool();
}

quint32 LayeredOptionsImpl::getRoutingOption() const
{
    return m_settings[LayoutOptionsGroup][RoutingOption].toUInt();
}

quint32 LayeredOptionsImpl::getLayoutDirection() const
{
    return m_settings[LayoutOptionsGroup][LayoutDirection].toUInt();
}

bool LayeredOptionsImpl::getInsideSelfLoops() const
{
    return m_settings[LayoutOptionsGroup][InsideSelfLoops].toBool();
}

quint32 LayeredOptionsImpl::getTextAndNode() const
{
    return m_settings[SpacingOptionsGroup][TextAndNode].toUInt();
}

quint32 LayeredOptionsImpl::getTextAndText() const
{
    return m_settings[SpacingOptionsGroup][TextAndText].toUInt();
}

quint32 LayeredOptionsImpl::getComponentAndComponent() const
{
    return m_settings[SpacingOptionsGroup][ComponentAndComponent].toUInt();
}

quint32 LayeredOptionsImpl::getEdgeAndEdgeH() const
{
    return m_settings[SpacingOptionsGroup][EdgeAndEdgeH].toUInt();
}

quint32 LayeredOptionsImpl::getEdgeAndEdgeV() const
{
    return m_settings[SpacingOptionsGroup][EdgeAndEdgeV].toUInt();
}

quint32 LayeredOptionsImpl::getEdgeAndEdge() const
{
    return m_settings[SpacingOptionsGroup][EdgeAndEdge].toUInt();
}

quint32 LayeredOptionsImpl::getEdgeAndLabel() const
{
    return m_settings[SpacingOptionsGroup][EdgeAndLabel].toUInt();
}

quint32 LayeredOptionsImpl::getEdgeAndNodeH() const
{
    return m_settings[SpacingOptionsGroup][EdgeAndNodeH].toUInt();
}

quint32 LayeredOptionsImpl::getEdgeAndNodeV() const
{
    return m_settings[SpacingOptionsGroup][EdgeAndNodeV].toUInt();
}

quint32 LayeredOptionsImpl::getLabelAndLabel() const
{
    return m_settings[SpacingOptionsGroup][LabelAndLabel].toUInt();
}

quint32 LayeredOptionsImpl::getLabelAndPortH() const
{
    return m_settings[SpacingOptionsGroup][LabelAndPortH].toUInt();
}

quint32 LayeredOptionsImpl::getLabelAndPortV() const
{
    return m_settings[SpacingOptionsGroup][LabelAndPortV].toUInt();
}

quint32 LayeredOptionsImpl::getNodeAndLabel() const
{
    return m_settings[SpacingOptionsGroup][NodeAndLabel].toUInt();
}

quint32 LayeredOptionsImpl::getNodeAndNodeH() const
{
    return m_settings[SpacingOptionsGroup][NodeAndNodeH].toUInt();
}

quint32 LayeredOptionsImpl::getNodeAndNodeV() const
{
    return m_settings[SpacingOptionsGroup][NodeAndNodeV].toUInt();
}

quint32 LayeredOptionsImpl::getNodeSelfLoop() const
{
    return m_settings[SpacingOptionsGroup][NodeSelfLoop].toUInt();
}

quint32 LayeredOptionsImpl::getPortAndPort() const
{
    return m_settings[SpacingOptionsGroup][PortAndPort].toUInt();
}

quint32 LayeredOptionsImpl::getSymbolAndSymbol() const
{
    return m_settings[SpacingOptionsGroup][SymbolAndSymbol].toUInt();
}

quint32 LayeredOptionsImpl::getPaddingTop() const
{
    return m_settings[SpacingOptionsGroup][PaddingTop].toUInt();
}

quint32 LayeredOptionsImpl::getPaddingBottom() const
{
    return m_settings[SpacingOptionsGroup][PaddingBottom].toUInt();
}

quint32 LayeredOptionsImpl::getPaddingLeft() const
{
    return m_settings[SpacingOptionsGroup][PaddingLeft].toUInt();
}

quint32 LayeredOptionsImpl::getPaddingRight() const
{
    return m_settings[SpacingOptionsGroup][PaddingRight].toUInt();
}

quint32 LayeredOptionsImpl::getAdditionalPortSpaceTop() const
{
    return m_settings[SpacingOptionsGroup][AdditionalPortSpaceTop].toUInt();
}

quint32 LayeredOptionsImpl::getAdditionalPortSpaceBottom() const
{
    return m_settings[SpacingOptionsGroup][AdditionalPortSpaceBottom].toUInt();
}

quint32 LayeredOptionsImpl::getAdditionalPortSpaceLeft() const
{
    return m_settings[SpacingOptionsGroup][AdditionalPortSpaceLeft].toUInt();
}

quint32 LayeredOptionsImpl::getAdditionalPortSpaceRight() const
{
    return m_settings[SpacingOptionsGroup][AdditionalPortSpaceRight].toUInt();
}

LayeredOptionsImpl::LayeredOptionsImpl()
{
    load();
    defaultAssign();
    printSettings();
}

void LayeredOptionsImpl::load()
{
    QString confPath = ":/LayeredOptions.ini";
    if (!QFile::exists(confPath)) {
        std::cout << "[Warning]The config file 'LayeredOptions.ini' was not found." << std::endl;
        return;
    }
    QSettings settings(confPath, QSettings::IniFormat);
    QStringList groups = settings.childGroups();
    for (const QString &group : groups) {
        settings.beginGroup(group);
        for (const QString &key : settings.childKeys()) {
            int keyType = m_settings[group][key].userType();
            QVariant value = settings.value(key);
            if (value.canConvert(keyType)) {
                value.convert(keyType);
            }
            m_settings[group][key] = value;
        }
        settings.endGroup();
    }
}

void LayeredOptionsImpl::defaultAssign()
{
    m_settings[LayoutOptionsGroup][SpacingIndividual] = true;       // 是否未图元指定单独的间距，与父对象的值不同
    m_settings[LayoutOptionsGroup][UnzippingLayerSplit] = false;    // 展开层的分割
    m_settings[LayoutOptionsGroup][RoutingOption] = 1;              // 布线策略(1: 正交布线)
    m_settings[LayoutOptionsGroup][LayoutDirection] = 2;            // 布局方向(1: ↑, 2: →, 3: ↓, 4: ←)
    m_settings[LayoutOptionsGroup][InsideSelfLoops] = false;        // 节点内部自环是否激活

    m_settings[SpacingOptionsGroup][TextAndNode] = 10;              // 文本和它关联的文本框之间的间距
    m_settings[SpacingOptionsGroup][TextAndText] = 10;              // 同一节点关联的文本框之间的间距
    m_settings[SpacingOptionsGroup][ComponentAndComponent] = 20;    // 组件之间的间距

    m_settings[SpacingOptionsGroup][EdgeAndEdgeH] = 10; // 边与边之间的水平间距
    m_settings[SpacingOptionsGroup][EdgeAndEdgeV] = 10; // 边与边之间的垂直间距
    m_settings[SpacingOptionsGroup][EdgeAndEdge] = 10;  // 边与边之间的整体间距
    m_settings[SpacingOptionsGroup][EdgeAndLabel] = 2;  // 边的标签与其关联的边之间的间
    m_settings[SpacingOptionsGroup][EdgeAndNodeH] = 10; // 边和节点之间的水平间距
    m_settings[SpacingOptionsGroup][EdgeAndNodeV] = 10; // 边和节点之间的垂直间距

    m_settings[SpacingOptionsGroup][LabelAndLabel] = 0; // 同一图形元素上的标签和标签之间的间距
    m_settings[SpacingOptionsGroup][LabelAndPortH] = 2; // 标签和其表征的端口之间的水平间距
    m_settings[SpacingOptionsGroup][LabelAndPortV] = 2; // 标签和其表征的端口之间的垂直间距

    m_settings[SpacingOptionsGroup][NodeAndLabel] = 5;  // 标签和其关联的节点的边框之间的间距
    m_settings[SpacingOptionsGroup][NodeAndNodeH] = 20; // 节点和节点之间的水平间距
    m_settings[SpacingOptionsGroup][NodeAndNodeV] = 20; // 节点和节点之间的垂直间距
    m_settings[SpacingOptionsGroup][NodeSelfLoop] = 10; // 节点和其自身循环边之间应该保留的间距

    m_settings[SpacingOptionsGroup][PortAndPort] = 5;      // 同一节点的成对端口之间的间距
    m_settings[SpacingOptionsGroup][SymbolAndSymbol] = 20; // 符号和符号之间的间距

    m_settings[SpacingOptionsGroup][PaddingTop] = 10;     // 位置最上的子节点和父节点的内边距
    m_settings[SpacingOptionsGroup][PaddingBottom] = 10;  // 位置最下的子节点和父节点的内边距
    m_settings[SpacingOptionsGroup][PaddingLeft] = 10;    // 位置最左的子节点和父节点的内边距
    m_settings[SpacingOptionsGroup][PaddingRight] = 10;   // 位置最右的子节点和父节点的内边距

    m_settings[SpacingOptionsGroup][AdditionalPortSpaceTop] = 2;    // 端口上方的额外空间
    m_settings[SpacingOptionsGroup][AdditionalPortSpaceBottom] = 2; // 端口下方的额外空间
    m_settings[SpacingOptionsGroup][AdditionalPortSpaceLeft] = 2;   // 端口左侧的额外空间
    m_settings[SpacingOptionsGroup][AdditionalPortSpaceRight] = 2;  // 端口右侧的额外空间
}

void LayeredOptionsImpl::printSettings() const
{

}
