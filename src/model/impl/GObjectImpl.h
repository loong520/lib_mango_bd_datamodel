//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "../../base/impl/ObjectImpl.h"
#include <QTransform>

namespace mango {
namespace blockdiagram {
namespace datamodel {

class GObjectImpl : public ObjectImpl {
public:
    GObjectImpl(Object *parent = nullptr) : ObjectImpl(parent)
    {
    }

    ObjectType getObjectType() const override { return ObjectType::kGObject; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;

    // 边界框
    virtual QRectF getBoundingRect() const;

    // 标志
    quint32 getFlags() const;
    void setFlags(quint32 flags);
    bool hasFlag(quint32 flag) const;
    void setFlag(quint32 flag, bool on);

    // 判断状态
    bool isSelected() const;
    bool isMoving() const;
    bool isModified() const;
    bool isVisible() const;
    bool isFixed() const;

    // 设置状态
    void setSelected(bool selected);
    void setMoving(bool moving);
    void setModified(bool modified);
    void setVisible(bool visible);
    void setFixed(bool fixed);

    // 位置
    void setPos(const QPointF& pos);
    QPointF getPos() const;

    // 移动
    void translate(const QPointF& offset);
    // 缩放
    void setScale(double scale);
    double getScale() const;
    // 旋转角度
    void setRotation(int angle);
    void setRotation(QPointF center, int angle);
    int getRotation() const;
    // 镜像
    void mirrorX();
    void mirrorY();
    // 矩阵变换
    QTransform getTransform() const;
    void concat(const QTransform& other);

    // z值
    int getZValue() const;
    void setZValue(int zValue);

    // 碰撞检测
    virtual bool hitTest(const QPointF &aPosition, int aAccuracy = 0) const;
    virtual bool hitTest(const QRectF &aRect, bool aContained, int aAccuracy = 0) const;

    // 边框宽度
    virtual int getBorderWidth() const;
    virtual void setBorderWidth(int width);

public:
    quint32 m_flags = 0;
    int     m_zValue = 0;
    QPointF m_pos;
    QTransform m_transform;
};

}
}
}
