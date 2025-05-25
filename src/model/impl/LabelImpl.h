//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GraphElementImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Label;
class GraphElement;

class LabelImpl : public GraphElementImpl {
public:
    static LabelImpl* New(GraphElementImpl* parent);

    LabelImpl(Object* parent = nullptr) : GraphElementImpl(parent) {}
    LabelImpl(const LabelImpl& other);
    LabelImpl* clone() const override;

    ObjectType getObjectType() const override { return ObjectType::kLabel; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    void setText(const QString& text);
    QString getText() const;

    void setType(LabelType type);
    LabelType getType() const;

public:
    QString m_text;
    LabelType m_type = LabelType::LabelForMainName;
};

}
}
}