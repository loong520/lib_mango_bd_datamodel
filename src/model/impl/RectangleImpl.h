//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Rectangle;
class Shape;

class RectangleImpl : public GObjectImpl {
public:
    static Rectangle* New(Shape* parent);

    RectangleImpl(Object* parent = nullptr) : GObjectImpl(parent)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kRectangle; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    void setTopLeft(const QPointF& topLeft);
    QPointF getTopLeft() const;

    void setWidth(double width);
    double getWidth() const;

    void setHeight(double height);
    double getHeight() const;

    void setSize(const QSize& size);
    QSize getSize() const;

public:
    QPointF m_topLeft = {0, 0};
    double  m_width = 0;
    double  m_height = 0;
};

}
}
}