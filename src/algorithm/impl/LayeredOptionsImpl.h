//
// Created by 18224 on 2025/5/26.
//
#pragma once

#include <QString>
#include <QVariant>

namespace mango {
namespace blockdiagram {
namespace datamodel {

#define DECL_SETTING_KEY(group, key) \
    inline static const QString key = #key

#define DECL_SETTING_GROUP(name) \
    inline static const QString name##Group = #name

/* setting group const */
DECL_SETTING_GROUP(LayoutOptions);
DECL_SETTING_GROUP(SpacingOptions);

/* setting key const */
// LayoutOptions
DECL_SETTING_KEY(LayoutOptionsGroup, SpacingIndividual);
DECL_SETTING_KEY(LayoutOptionsGroup, UnzippingLayerSplit);
DECL_SETTING_KEY(LayoutOptionsGroup, RoutingOption);
DECL_SETTING_KEY(LayoutOptionsGroup, LayoutDirection);
DECL_SETTING_KEY(LayoutOptionsGroup, InsideSelfLoops);
// SpacingOptions
// text
DECL_SETTING_KEY(SpacingOptionsGroup, TextAndNode);
DECL_SETTING_KEY(SpacingOptionsGroup, TextAndText);
DECL_SETTING_KEY(SpacingOptionsGroup, ComponentAndComponent);
// edge
DECL_SETTING_KEY(SpacingOptionsGroup, EdgeAndEdgeH);
DECL_SETTING_KEY(SpacingOptionsGroup, EdgeAndEdgeV);
DECL_SETTING_KEY(SpacingOptionsGroup, EdgeAndEdge);
DECL_SETTING_KEY(SpacingOptionsGroup, EdgeAndLabel);
DECL_SETTING_KEY(SpacingOptionsGroup, EdgeAndNodeH);
DECL_SETTING_KEY(SpacingOptionsGroup, EdgeAndNodeV);
// label
DECL_SETTING_KEY(SpacingOptionsGroup, LabelAndLabel);
DECL_SETTING_KEY(SpacingOptionsGroup, LabelAndPortH);
DECL_SETTING_KEY(SpacingOptionsGroup, LabelAndPortV);
// node
DECL_SETTING_KEY(SpacingOptionsGroup, NodeAndLabel);
DECL_SETTING_KEY(SpacingOptionsGroup, NodeAndNodeH);
DECL_SETTING_KEY(SpacingOptionsGroup, NodeAndNodeV);
DECL_SETTING_KEY(SpacingOptionsGroup, NodeSelfLoop);
// port
DECL_SETTING_KEY(SpacingOptionsGroup, PortAndPort);
// symbol
DECL_SETTING_KEY(SpacingOptionsGroup, SymbolAndSymbol);
// padding
DECL_SETTING_KEY(SpacingOptionsGroup, PaddingTop);
DECL_SETTING_KEY(SpacingOptionsGroup, PaddingBottom);
DECL_SETTING_KEY(SpacingOptionsGroup, PaddingLeft);
DECL_SETTING_KEY(SpacingOptionsGroup, PaddingRight);
// port spacing
DECL_SETTING_KEY(SpacingOptionsGroup, AdditionalPortSpaceTop);
DECL_SETTING_KEY(SpacingOptionsGroup, AdditionalPortSpaceBottom);
DECL_SETTING_KEY(SpacingOptionsGroup, AdditionalPortSpaceLeft);
DECL_SETTING_KEY(SpacingOptionsGroup, AdditionalPortSpaceRight);


class LayeredOptionsImpl {
public:
    static LayeredOptionsImpl &instance();

    bool getSpacingIndividual() const;
    bool getUnzippingLayerSplit() const;
    quint32 getRoutingOption() const;
    quint32 getLayoutDirection() const;
    bool getInsideSelfLoops() const;

    quint32 getTextAndNode() const;
    quint32 getTextAndText() const;
    quint32 getComponentAndComponent() const;
    quint32 getEdgeAndEdgeH() const;
    quint32 getEdgeAndEdgeV() const;
    quint32 getEdgeAndEdge() const;
    quint32 getEdgeAndLabel() const;
    quint32 getEdgeAndNodeH() const;
    quint32 getEdgeAndNodeV() const;

    quint32 getLabelAndLabel() const;
    quint32 getLabelAndPortH() const;
    quint32 getLabelAndPortV() const;

    quint32 getNodeAndLabel() const;
    quint32 getNodeAndNodeH() const;
    quint32 getNodeAndNodeV() const;
    quint32 getNodeSelfLoop() const;

    quint32 getPortAndPort() const;
    quint32 getSymbolAndSymbol() const;

    quint32 getPaddingTop() const;
    quint32 getPaddingBottom() const;
    quint32 getPaddingLeft() const;
    quint32 getPaddingRight() const;

    quint32 getAdditionalPortSpaceTop() const;
    quint32 getAdditionalPortSpaceBottom() const;
    quint32 getAdditionalPortSpaceLeft() const;
    quint32 getAdditionalPortSpaceRight() const;

private:
    LayeredOptionsImpl();
    LayeredOptionsImpl(const LayeredOptionsImpl&) = delete;
    LayeredOptionsImpl& operator=(const LayeredOptionsImpl&) = delete;

    void load();

    void defaultAssign();

    void printSettings() const;

public:
    QHash<QString, QHash<QString, QVariant>> m_settings;
};

} // end of namespace datamodel
} // end of namespace blockdiagram
} // end of namespace mango

