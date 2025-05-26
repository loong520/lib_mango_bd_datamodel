//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GObject.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Shape;

class MANGO_BD_DATAMODEL_API Arc : public GObject {
public:
    static Arc* New(Shape* parent);
    static Arc* New(Shape* parent, double radius, const QPointF& center, double startAngle, double spanAngle);

    /// 克隆对象
    /// \return 克隆的对象指针
    Arc *clone() const;

    /// 设置圆心坐标
    /// \param center 圆心坐标
    void setCenter(const QPointF center);

    /// 获取圆心坐标
    /// \return 圆心坐标
    QPointF getCenter() const;

    /// 设置半径
    /// \param radius 半径
    void setRadius(double radius);

    /// 获取半径
    /// \return 半径
    double getRadius() const;

    /// 设置起始角度
    /// \param startAngle 起始角度
    void setStartAngle(double startAngle);

    /// 获取起始角度
    /// \return 起始角度
    double getStartAngle() const;

    /// 设置跨度角度
    /// \param spanAngle 跨度角度
    void setSpanAngle(double spanAngle);

    /// 获取跨度角度
    /// \return 跨度角度
    double getSpanAngle() const;
};

}
}
}