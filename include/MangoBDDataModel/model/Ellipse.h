//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GObject.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Shape;

class MANGO_BD_DATAMODEL_API Ellipse : public GObject {
public:
    static Ellipse* New(Shape* parent);
    static Ellipse* New(Shape* parent, double radiusX, double radiusY, const QPointF& center);

    /// 克隆对象
    /// \return 克隆的对象指针
    Ellipse* clone() const;

    /// 设置椭圆的圆心坐标
    /// \param center 圆心坐标
    void setCenter(const QPointF& center);

    /// 获取椭圆的圆心坐标
    /// \return 圆心坐标
    QPointF getCenter() const;

    /// 设置椭圆的半径x
    /// \param radiusX 半径x
    void setRadiusX(double radiusX);

    /// 获取椭圆的半径x
    /// \return 半径x
    double getRadiusX() const;

    /// 设置椭圆的半径y
    /// \param radiusY 半径y
    void setRadiusY(double radiusY);

    /// 获取椭圆的半径y
    /// \return 半径y
    double getRadiusY() const;

public:
    QPointF m_center = {0, 0};  // 圆心坐标(相对于pos的相对坐标，默认把pos作为原点)
    double m_radiusX = 0;       // 半径x
    double m_radiusY = 0;       // 半径y
};

}
}
}