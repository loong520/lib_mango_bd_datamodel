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

    void setTopLeft(const QPointF& topLeft);
    QPointF getTopLeft() const;

    void setWidth(double width);
    double getWidth() const;

    void setHeight(double height);
    double getHeight() const;

    void setSize(const QSize& size);
    QSize getSize() const;

public:
    QPointF m_topLeft;
    double  m_width;
    double  m_height;
};

}
}
}