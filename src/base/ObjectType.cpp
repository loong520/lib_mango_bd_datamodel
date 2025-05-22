//
// Created by 18224 on 2025/5/7.
//
#include "MangoBDDataModel/base/ObjectType.h"

#include <QHash>

using namespace mango::blockdiagram::datamodel;

namespace
{

// 定义映射宏
#define TYPEID_MAP(XX) \
    XX(kUnknown, "Unknown") \
    XX(kObject, "Object") \
    XX(kGObject, "GObject") \
    XX(kRectangle, "Rectangle") \
    XX(kEllipse, "Ellipse")   \
    XX(kPolygon, "Polygon") \
    XX(kPolyline, "Polyline") \
    XX(kArc, "Arc") \
    XX(kShape, "Shape") \
    XX(kGraphElement, "GraphElement") \
    XX(kLabel, "Label") \
    XX(kNode, "Node") \
    XX(kPin, "Pin") \
    XX(kCompositePin, "CompositePin") \
    XX(kSymbol, "Symbol") \
    XX(kNet, "Net") \
    XX(kEdgeSection, "EdgeSection") \
    XX(kRTree, "RTree") \
    XX(kStyle, "Style") \
    XX(kTheme, "Theme") \
    XX(kStyleManager, "StyleManager") \
    XX(kMaxObjectTypes, "kMaxObjectTypes")

// 生成枚举到字符串的映射
QHash<ObjectType::TypeId, QString> createType2StringMap()
{
    QHash<ObjectType::TypeId, QString> map;
#define XX(id, name) map[ObjectType::id] = name;
    TYPEID_MAP(XX)
#undef XX
    return map;
}

// 生成字符串到枚举的映射
QHash<QString,ObjectType::TypeId> createString2TypeMap()
{
    QHash<QString, ObjectType::TypeId> map;
#define XX(id, name) map[name] = ObjectType::id;
    TYPEID_MAP(XX)
#undef XX
    return map;
}

}

ObjectType::ObjectType()
    : m_type(ObjectType::kUnknown)
{
}

ObjectType::ObjectType(ObjectType::TypeId type) : m_type(type)
{
    if (type < kUnknown || type >= kMaxObjectTypes) {
        m_type = kUnknown;
    }
}

ObjectType::ObjectType(const QString &typeName)
{
    static const QHash<QString,ObjectType::TypeId> stringToType = createString2TypeMap();
    m_type = stringToType.value(typeName, kUnknown);
}

const QString ObjectType::getName() const
{
    static const QHash<ObjectType::TypeId, QString> type2StringMap = createType2StringMap();
    return type2StringMap.value(m_type, type2StringMap[kUnknown]);
}

ObjectType::TypeId ObjectType::getType() const
{
    return m_type;
}

ObjectType::operator quint16() const
{
    return m_type;
}

ObjectType::operator TypeId() const
{
    return m_type;
}

bool ObjectType::operator==(quint16 right) const
{
    return this->m_type == right;
}

bool ObjectType::operator==(ObjectType::TypeId right) const
{
    return this->m_type == right;
}

bool ObjectType::operator!=(ObjectType::TypeId right) const
{
    return this->m_type != right;
}

bool ObjectType::operator==(const ObjectType &right) const
{
    return this->m_type == right.m_type;
}

bool ObjectType::operator!=(const ObjectType &right) const
{
    return this->m_type != right.m_type;
}
