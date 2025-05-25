//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class ShapeImpl;

class EllipseImpl : public GObjectImpl {
public:
    static EllipseImpl* New(ShapeImpl* parent);
    static EllipseImpl* New(ShapeImpl* parent, double radiusX, double radiusY, const QPointF& center);

    EllipseImpl(double radiusX, double radiusY, const QPointF& center, Object* parent = nullptr)
        : GObjectImpl(parent), m_radiusX(radiusX), m_radiusY(radiusY), m_center(center)
    {
    }
    EllipseImpl(const EllipseImpl &other);
    EllipseImpl* clone() const override;

    ObjectType getObjectType() const override { return ObjectType::kEllipse; }
    bool isTypeOf(const ObjectType &type) const override;
    void Delete() override;
    QRectF getBoundingRect() const override;

    // 命中测试
    bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const override;
    bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const override;

    // 圆心
    void setCenter(const QPointF& center);
    QPointF getCenter() const;

    // x半径
    void setRadiusX(double radiusX);
    double getRadiusX() const;

    // y半径
    void setRadiusY(double radiusY);
    double getRadiusY() const;

public:
    QPointF m_center = {0, 0};  // 圆心坐标(相对于pos的相对坐标，默认把pos作为原点)
    double m_radiusX = 0;       // 半径x
    double m_radiusY = 0;       // 半径y
};

}
}
}