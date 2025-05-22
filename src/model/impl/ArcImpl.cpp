//
// Created by 18224 on 2025/5/7.
//

#include "ArcImpl.h"
#include "ShapeImpl.h"
#include "NodeImpl.h"
#include <QtMath>

using namespace mango::blockdiagram::datamodel;

Arc* ArcImpl::New(Shape* parent)
{
    return New(parent, 0.0, {}, 0.0, 0.0);
}

Arc* ArcImpl::New(Shape* parent, double radius, const QPointF& center, double startAngle, double spanAngle)
{
    if (!parent) {
        // TODO: LOG_WARN
        return nullptr;
    }
    ArcImpl* impl = new ArcImpl(radius, center, startAngle, spanAngle, (Object*)parent);

    obj_impl_ptr(Shape, parent)->addSubShape((GObjectImpl*)impl);

    return (Arc*)impl;
}

bool ArcImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kArc) {
        return true;
    }
    return false;
}

void ArcImpl::Delete()
{
    if (!m_parent) {
        // TODO: LOG_ERROR
        return;
    }

    ObjectType::TypeId typeId = m_parent->getObjectType();
    if (typeId == ObjectType::kShape) {
        obj_impl_ptr(Shape, m_parent)->removeSubShape((GObjectImpl*)this);
    } else if (typeId == ObjectType::kNode) {
        obj_impl_ptr(Node, m_parent)->removeGraphElement(this);
    } else {
        // TODO: LOG_ERROR
    }
}

QRectF ArcImpl::getBoundingRect() const
{
    // 圆心坐标（以pos为原点的相对坐标）
    QPointF center = m_center;
    double radius = m_radius;

    // 构造初始的边界框：完整圆的边界
    QRectF boundingBox(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);

    // 如果是整圆或半圆等标准情况，直接返回整个圆的包围盒
    if (qFuzzyIsNull(m_spanAngle) || qAbs(m_spanAngle) >= 360.0) {
        // 加上边框宽度的一半
        if (auto bw = getBorderWidth() / 2.0; bw > 0.00001) {
            boundingBox.adjust(-bw, -bw, bw, bw);
        }
        boundingBox = m_transform.mapRect(boundingBox);
        return boundingBox;
    }

    // 如果是部分圆弧，我们需要计算该弧线经过的所有极值角度点（0°, 90°, 180°, 270°）
    // Qt 的角度是逆时针，0 度是 x 轴正方向

    double startDeg = m_startAngle;
    double endDeg = m_startAngle + m_spanAngle;

    // 规范化角度范围到 [0, 360)
    auto normalize = [](double angle) -> double {
        while (angle < 0) {
            angle += 360.0;
        }
        while (angle >= 360.0) {
            angle -= 360.0;
        }
        return angle;
    };

    // 计算极值角度点（0°, 90°, 180°, 270°）是否在弧段内
    QList<double> anglesToTest = { startDeg, endDeg };
    for (int a : {0, 90, 180, 270}) {
        double normA = normalize(a);
        double normStart = normalize(startDeg);
        double normEnd = normalize(endDeg);

        // 判断 normA 是否在 [normStart, normEnd] 范围内（考虑正负 span）
        bool inSpan = false;
        if (m_spanAngle > 0) {
            inSpan = (normStart < normEnd)
                     ? (normA >= normStart && normA <= normEnd)
                     : (normA >= normStart || normA <= normEnd);
        } else {
            inSpan = (normStart > normEnd)
                     ? (normA <= normStart && normA >= normEnd)
                     : (normA <= normStart || normA >= normEnd);
        }

        if (inSpan) {
            anglesToTest.append(a);
        }
    }

    // 计算所有关键角度对应的点，更新边界
    QRectF result;
    for (double angle : anglesToTest) {
        double rad = qDegreesToRadians(angle);
        QPointF pt(center.x() + radius * std::cos(rad), center.y() - radius * std::sin(rad));  // y轴向下
        result |= QRectF(pt, pt);  // 扩展 result
    }

    return result;
}

bool ArcImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool ArcImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
}

void ArcImpl::setCenter(const QPointF center)
{
    m_center = center;
}

QPointF ArcImpl::getCenter() const
{
    return m_center;
}

void ArcImpl::setRadius(double radius)
{
    m_radius = radius;
}

double ArcImpl::getRadius() const
{
    return m_radius;
}

void ArcImpl::setStartAngle(double startAngle)
{
    m_startAngle = startAngle;
}

double ArcImpl::getStartAngle() const
{
    return m_startAngle;
}

void ArcImpl::setSpanAngle(double spanAngle)
{
    m_spanAngle = spanAngle;
}

double ArcImpl::getSpanAngle() const
{
    return m_spanAngle;
}