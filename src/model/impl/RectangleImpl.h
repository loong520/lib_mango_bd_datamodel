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
    static Rectangle* New(Shape* parent, const QRectF &rect);

    RectangleImpl(const QRectF &rect, Object* parent = nullptr)
        : GObjectImpl(parent), m_rect(rect)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kRectangle; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    void setRect(const QRectF &rect);
    inline QRectF getRect() const { return m_rect;}

    void setTopLeft(const QPointF& topLeft);
    inline QPointF getTopLeft() const { return m_rect.topLeft(); }

    void setWidth(double width);
    inline double getWidth() const { return m_rect.width(); }

    void setHeight(double height);
    inline double getHeight() const { return m_rect.height();}

    void setSize(const QSizeF& size);
    inline QSizeF getSize() const { return m_rect.size(); }

    inline bool isValid() const noexcept { return m_rect.isValid(); }

public:
    QRectF m_rect;
};

}
}
}