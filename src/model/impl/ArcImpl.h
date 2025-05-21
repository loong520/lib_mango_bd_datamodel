//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Arc;
class Shape;

class ArcImpl : public GObjectImpl {
public:
    static Arc* New(Shape* parent);

    ArcImpl(Object* parent = nullptr) : GObjectImpl(parent)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kArc; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    void setCenter(const QPointF center);
    QPointF getCenter() const;

    void setRadius(double radius);
    double getRadius() const;

    void setStartAngle(double startAngle);
    double getStartAngle() const;

    void setSpanAngle(double spanAngle);
    double getSpanAngle() const;

public:
    QPointF m_center = {0, 0};  // 圆心坐标(相对于pos的相对坐标，默认把pos作为原点)
    double m_radius = 0;        // 半径
    double m_startAngle = 0;    // 起始角度
    double m_spanAngle = 0;     // 角度
};

}
}
}