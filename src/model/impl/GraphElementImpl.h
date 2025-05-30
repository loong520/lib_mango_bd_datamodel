//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class LabelImpl;
class NodeImpl;
class ShapeImpl;

class GraphElementImpl : public GObjectImpl {
public:
    static GraphElementImpl* New(NodeImpl* parent);

    GraphElementImpl(Object* parent = nullptr);
    GraphElementImpl(const GraphElementImpl &other);
    GraphElementImpl* clone() const override;

    ObjectType getObjectType() const override { return ObjectType::kGraphElement; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    // 名字
    void setName(const QString& name);
    QString getName() const;

    // 形状
    void setShape(ShapeImpl *shape);
    ShapeImpl *getShape() const;

    // 文本
    void addLabel(LabelImpl *label);
    void removeLabel(LabelImpl *label);
    QList<LabelImpl*> getLabels() const;

    /// 查找主名字标签
    /// @param element 元素
    /// @return 主名字标签
    static LabelImpl* findMainName(const GraphElementImpl* element);

public:
    QList<LabelImpl *> m_labels;
    ShapeImpl *m_shape = nullptr;
};

}
}
}