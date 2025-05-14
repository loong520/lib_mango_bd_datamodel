//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class LabelImpl;
class Node;
class GraphElement;
class ShapeImpl;

class GraphElementImpl : public GObjectImpl {
public:
    static GraphElement* New(Node* parent);

    GraphElementImpl(Object* parent = nullptr);

    ObjectType getObjectType() const override { return ObjectType::kGraphElement; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;

    QRectF getBoundingRect() const override;

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