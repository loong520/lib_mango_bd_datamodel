//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElementImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class PinImpl;

class NetImpl : public GraphElementImpl {
public:
    static NetImpl* New(NodeImpl* parent);

    NetImpl(Object* parent = nullptr) : GraphElementImpl(parent) {}
    NetImpl(const NetImpl &other);
    NetImpl* clone() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    // 源端
    void addSource(PinImpl* pin);
    void removeSource(PinImpl* pin);
    QList<PinImpl*> getSources() const;

    // 目标端
    void addTarget(PinImpl* pin);
    void removeTarget(PinImpl* pin);
    QList<PinImpl*> getTargets() const;

    // 连线模式
    void setConnectMode(ConnectMode mode);
    ConnectMode getConnectMode() const;

    // 样式
    int getLineWidth() const;
    QString getLineColor() const;

public:
    QList<PinImpl*> m_sources;
    QList<PinImpl*> m_targets;
    ConnectMode m_connectMode = ConnectModeFly; // 默认为飞线模式
};

}
}
}