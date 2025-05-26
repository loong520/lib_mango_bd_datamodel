//
// Created by 18224 on 2025/5/26.
//

#include "MangoBDDataModel/algorithm/LayeredOptions.h"
#include "MangoBDDataModel/base/Object.h"
#include "impl/LayeredOptionsImpl.h"

using namespace mango::blockdiagram::datamodel;

LayeredOptions &LayeredOptions::instance()
{
    return (LayeredOptions &)(LayeredOptionsImpl::instance());
}

bool LayeredOptions::getSpacingIndividual() const
{
    return impl_ptr(LayeredOptions)->getSpacingIndividual();
}

bool LayeredOptions::getUnzippingLayerSplit() const
{
    return impl_ptr(LayeredOptions)->getUnzippingLayerSplit();
}

quint32 LayeredOptions::getRoutingOption() const
{
    return impl_ptr(LayeredOptions)->getRoutingOption();
}

quint32 LayeredOptions::getLayoutDirection() const
{
    return impl_ptr(LayeredOptions)->getLayoutDirection();
}

bool LayeredOptions::getInsideSelfLoops() const
{
    return impl_ptr(LayeredOptions)->getInsideSelfLoops();
}

quint32 LayeredOptions::getTextAndNode() const
{
    return impl_ptr(LayeredOptions)->getTextAndNode();
}

quint32 LayeredOptions::getTextAndText() const
{
    return impl_ptr(LayeredOptions)->getTextAndText();
}

quint32 LayeredOptions::getComponentAndComponent() const
{
    return impl_ptr(LayeredOptions)->getComponentAndComponent();
}

quint32 LayeredOptions::getEdgeAndEdgeH() const
{
    return impl_ptr(LayeredOptions)->getEdgeAndEdgeH();
}

quint32 LayeredOptions::getEdgeAndEdgeV() const
{
    return impl_ptr(LayeredOptions)->getEdgeAndEdgeV();
}

quint32 LayeredOptions::getEdgeAndEdge() const
{
    return impl_ptr(LayeredOptions)->getEdgeAndEdge();
}

quint32 LayeredOptions::getEdgeAndLabel() const
{
    return impl_ptr(LayeredOptions)->getEdgeAndLabel();
}

quint32 LayeredOptions::getEdgeAndNodeH() const
{
    return impl_ptr(LayeredOptions)->getEdgeAndNodeH();
}

quint32 LayeredOptions::getEdgeAndNodeV() const
{
    return impl_ptr(LayeredOptions)->getEdgeAndNodeV();
}

quint32 LayeredOptions::getLabelAndLabel() const
{
    return impl_ptr(LayeredOptions)->getLabelAndLabel();
}

quint32 LayeredOptions::getLabelAndPortH() const
{
    return impl_ptr(LayeredOptions)->getLabelAndPortH();
}

quint32 LayeredOptions::getLabelAndPortV() const
{
    return impl_ptr(LayeredOptions)->getLabelAndPortV();
}

quint32 LayeredOptions::getNodeAndLabel() const
{
    return impl_ptr(LayeredOptions)->getNodeAndLabel();
}

quint32 LayeredOptions::getNodeAndNodeH() const
{
    return impl_ptr(LayeredOptions)->getNodeAndNodeH();
}

quint32 LayeredOptions::getNodeAndNodeV() const
{
    return impl_ptr(LayeredOptions)->getNodeAndNodeV();
}

quint32 LayeredOptions::getNodeSelfLoop() const
{
    return impl_ptr(LayeredOptions)->getNodeSelfLoop();
}

quint32 LayeredOptions::getPortAndPort() const
{
    return impl_ptr(LayeredOptions)->getPortAndPort();
}

quint32 LayeredOptions::getSymbolAndSymbol() const
{
    return impl_ptr(LayeredOptions)->getSymbolAndSymbol();
}

quint32 LayeredOptions::getPaddingTop() const
{
    return impl_ptr(LayeredOptions)->getPaddingTop();
}

quint32 LayeredOptions::getPaddingBottom() const
{
    return impl_ptr(LayeredOptions)->getPaddingBottom();
}

quint32 LayeredOptions::getPaddingLeft() const
{
    return impl_ptr(LayeredOptions)->getPaddingLeft();
}

quint32 LayeredOptions::getPaddingRight() const
{
    return impl_ptr(LayeredOptions)->getPaddingRight();
}

quint32 LayeredOptions::getAdditionalPortSpaceTop() const
{
    return impl_ptr(LayeredOptions)->getAdditionalPortSpaceTop();
}

quint32 LayeredOptions::getAdditionalPortSpaceBottom() const
{
    return impl_ptr(LayeredOptions)->getAdditionalPortSpaceBottom();
}

quint32 LayeredOptions::getAdditionalPortSpaceLeft() const
{
    return impl_ptr(LayeredOptions)->getAdditionalPortSpaceLeft();
}

quint32 LayeredOptions::getAdditionalPortSpaceRight() const
{
    return impl_ptr(LayeredOptions)->getAdditionalPortSpaceRight();
}