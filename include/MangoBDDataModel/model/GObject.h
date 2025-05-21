//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/base/Object.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class MANGO_BD_DATAMODEL_API GObject : public Object {
public:

    /// 获取标志
    /// @return 标志
    quint32 getFlags() const;

    /// 设置标志
    /// @param flags 标志
    void setFlags(quint32 flags);

    /// 检查是否存在指定的标志
    /// @param flag 要检查的标志
    /// @return 如果存在指定的标志，则返回true，否则返回false
    bool hasFlag(quint32 flag) const;

    /// 设置指定的标志
    /// @param flag 要设置的标志
    /// @param on 如果为true，则设置标志，否则清除标志
    void setFlag(quint32 flag, bool on);

    /// 是否被选中
    /// @return 如果被选中，则返回true，否则返回false
    bool isSelected() const;

    /// 是否被移动
    /// @return 如果被移动，则返回true，否则返回false
    bool isMoving() const;

    /// 是否被修改
    /// @return 如果被修改，则返回true，否则返回false
    bool isModified() const;

    /// 是否可见
    /// @return 如果可见，则返回true，否则返回false
    bool isVisible() const;

    /// 是否固定
    /// @return 如果固定，则返回true，否则返回false
    bool isFixed() const;

    /// 设置选中状态
    /// @param selected 选中状态
    void setSelected(bool selected);

    /// 设置移动状态
    /// @param moving 移动状态
    void setMoving(bool moving);

    /// 设置修改状态
    /// @param modified 修改状态
    void setModified(bool modified);

    /// 设置可见状态
    /// @param visible 可见状态
    void setVisible(bool visible);

    /// 设置固定状态
    /// @param fixed 固定状态
    void setFixed(bool fixed);

    /// 获取边界框
    /// @return 边界框
    QRectF getBoundingRect() const;

    /// 获取位置
    /// @return 位置
    QPointF getPos() const;

    /// 设置位置
    /// @param pos 位置
    void setPos(const QPointF& pos);

    /// 移动
    /// @param offset 偏移量
    void translate(const QPointF& offset);

    /// 移动
    /// @param dx x轴偏移量
    /// @param dy y轴偏移量
    void translate(double dx, double dy);

    /// 设置缩放比例
    /// @param scale 缩放比例
    void setScale(double scale);

    /// 获取缩放比例
    /// @return 缩放比例
    double getScale() const;

    /// 获取旋转角度
    /// @return 旋转角度
    int getRotation() const;

    /// 设置旋转角度
    /// @param angle 旋转角度
    void setRotation(int angle);

    /// 设置旋转角度
    /// @param center 旋转中心
    /// @param angle 旋转角度
    void setRotation(QPointF center, int angle);

    /// x轴镜像
    void mirrorX();

    /// y轴镜像
    void mirrorY();

    /// 获取变换矩阵
    /// @return 变换矩阵
    QTransform getTransform() const;

    /// 叠加变化矩阵
    /// @param other 变换矩阵
    void concat(const QTransform& other);

    /// 获取z值
    /// @return z值
    int getZValue() const;

    /// 设置z值
    /// @param zValue z值
    void setZValue(int zValue);

    /// 测试点是否在该项内部或边界上
    /// @param aPosition 点
    /// @param aAccuracy 精度(GObject的边框基础上再进行外扩或者内缩)
    /// @return 如果点在图形内，则返回true，否则返回false
    bool hitTest(const QPointF& aPosition, int aAccuracy = 0) const;

    /// 测试矩形是否与该项相交
    /// @param aRect 矩形
    /// @param aContained 是否包含
    /// @param aAccuracy 精度（aRect基础上外扩或者内缩）
    /// @return 如果矩形在图形内，则返回true，否则返回false
    bool hitTest(const QRectF& aRect, bool aContained, int aAccuracy = 0) const;

    /// 获取边框宽度
    /// @return 边框宽度
    int getBorderWidth() const;

    /// 设置边框宽度
    /// @param width 边框宽度
    void setBorderWidth(int width);

};

}
}
}
