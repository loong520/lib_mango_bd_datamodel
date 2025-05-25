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
        kLibSymbol = 90,        ///< "LibSymbol"
        kEdgeSection = 100,     ///< "EdgeSection"
        kRTree = 110,           ///< "RTree"
        kStyle = 120,           ///< "Style"
        kTheme = 130,           ///< "Theme"
        kStyleManager = 140,    ///< "StyleManager"

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

} // end of namespace datamodel
} // end of namespace blockdiagram
} // end of namespace mango

