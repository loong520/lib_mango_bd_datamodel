//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include <QList>
#include <QPointF>
#include <QRectF>

#include "MangoBDDataModel/base/Config.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class MANGO_BD_DATAMODEL_API ObjectType {
public:
    /// @details 类型ID
    enum TypeId : quint16 {
        kUnknown = 0,           ///< "Unknown"
        kObject = 1,            ///< "Object"
        kGObject = 2,           ///< "GObject"
        kRectangle = 3,         ///< "Rectangle"
        kEllipse = 4,           ///< "Ellipse"
        kPolygon = 5,           ///< "Polygon"
        kPolyline = 6,          ///< "Polyline"
        kArc = 7,               ///< "Arc"
        kShape = 10,            ///< "Shape"
        kGraphElement = 20,     ///< "GraphElement"
        kLabel = 30,            ///< "Label"
        kNode = 40,             ///< "Node"
        kPin = 50,              ///< "Pin"
        kCompositePin = 60,     ///< "CompositePin"
        kSymbol = 70,           ///< "Symbol"
        kNet = 80,              ///< "Net"
        kEdgeSection = 90,      ///< "EdgeSection"
        kRTree = 100,           ///< "RTree"
        kStyle = 110,           ///< "Style"
        kTheme = 120,           ///< "Theme"
        kStyleManager = 130,    ///< "StyleManager"

        kMaxObjectTypes = 200, ///< "kMaxObjectTypes"
    };
    ObjectType();

    /// 构造函数
    /// @param type 类型ID
    ObjectType(TypeId type);

    /// 析构函数
    /// @param typeName 类型名称
    ObjectType(const QString& typeName);

    /// 获取对象类型名称
    /// @return 类型名称
    const QString getName() const;

    /// 获取对象类型ID
    /// @return 类型ID
    TypeId getType() const;

    /// 转换为quint16类型
    /// @return 类型ID
    operator quint16() const;

    /// 转换为TypeId类型
    /// \return 类型ID
    operator TypeId() const;

    /// 相等比较
    /// \param right 与之比较的值是 quint16 的类型
    /// \return 是否相等
    bool operator==(quint16 right) const;

    /// 相等比较
    /// \param right 与之比较的值是 TypeId 的类型
    /// \return 是否相等
    bool operator==(ObjectType::TypeId right) const;
    bool operator!=(ObjectType::TypeId right) const;

    /// 相等比较
    /// \param right 与之比较的值是 ObjectType 的类型
    /// \return 是否相等
    bool operator==(const ObjectType& right) const;
    bool operator!=(const ObjectType& right) const;

private:
    TypeId m_type;
};


enum MANGO_BD_DATAMODEL_API GObjectFlag {
    ObjectIsSelected = 0x1,
    ObjectIsMoving = 0x2,
    ObjectIsModified = 0x4,
    ObjectIsVisible = 0x8,
    ObjectIsFixed = 0x10,
};

enum MANGO_BD_DATAMODEL_API LabelType {
    LabelForMainName,
    LabelForComment,
};

enum MANGO_BD_DATAMODEL_API ConnectMode {
    ConnectModeFly = 0, // 飞线
    ConnectModeNamed,   // 命名连线
    ConnectModeDirect,  // 直接连线
};

enum MANGO_BD_DATAMODEL_API Direction {
    Bottom = 0,
    Top = 1,
    Left = 2,
    Right = 3,
    Middle = 4,
};

enum MANGO_BD_DATAMODEL_API PinShape {
    Line = 0,
    Inverted,
    Clock,
    InvertedClock,
    InputLow,
    ClockLow,
    OutputLow,
    FallingEdgeClock,
    NonLogic,

    LastOption = NonLogic, ///< this is the sentinel value, must be set to last enum value
    Inherit
};

/// 定义图元外观的改变程度
enum GObjectUpdateFlags {
    None        = 0x00,     ///< 无需更新
    Appearance  = 0x01,     ///< 可见性标志已更改
    Color       = 0x02,     ///< 颜色已经改变
    Geometry    = 0x04,     ///< 位置或形状已发生变化
    Layers      = 0x08,     ///< 图层已更改
    Initial_Add = 0x10,     ///< 项目正在添加到视图中
    Repaint     = 0x20,     ///< 物品需要重新绘制
    All         = 0xef      ///< 除了 Initial_Add 之外的所有内容
};

} // end of namespace datamodel
} // end of namespace blockdiagram
} // end of namespace mango

