//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "GObject.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class Shape;

class MANGO_BD_DATAMODEL_API Rectangle : public GObject {
public:

    /// 创建一个新的矩形对象
    /// \param parent 父对象
    /// \return 折线对象指针
    static Rectangle* New(Shape* parent);

    /// 设置矩形的左上角坐标
    /// \param topLeft 左上角坐标
    void setTopLeft(const QPointF& topLeft);

    /// 获取矩形的左上角坐标
    /// \return 左上角坐标
    QPointF getTopLeft() const;

    /// 设置矩形的宽度
    /// \param width 宽度
    void setWidth(double width);

    /// 获取矩形的宽度
    /// \return 宽度
    double getWidth() const;

    /// 设置矩形的高度
    /// \param height 高度
    void setHeight(double height);

    /// 获取矩形的高度
    /// \return 高度
    double getHeight() const;

    /// 获取矩形的大小
    /// \param size 大小
    void setSize(const QSize& size);

    /// 获取矩形的大小
    /// \return 大小
    QSize getSize() const;
};

}
}
}