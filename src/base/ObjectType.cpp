//
// Created by 18224 on 2025/5/7.
//
#include "ObjectType.h"

#include <QHash>

using namespace mango::blockdiagram::datamodel;

namespace
{
const QString kNames[] = {
    "GObject",
    "GObject",
    "Unknown"
    "Object"
    "GObject"
    "Rectangle"
    "Elipse"
    "Polygon"
    "Polyline"
    "Arc"
    "Shape"
    "GraphElement"
    "Label"
    "Node"
    "Pin"
    "CompositePin"
    "Symbol"
    "Net"
    "EdgeSection"
    "RTree"
    "Style"
    "Theme"
    "StyleManager"
    "kMaxObjectTypes"
};
QHash<QString, quint16> kNameToType;

class NameToTypeInitializer {
public:
    NameToTypeInitializer()
    {
        for (quint16 i = 0; i < ObjectType::kMaxObjectTypes; ++i) {
            kNameToType[kNames[i]] = i;
        }
    }
};

const static NameToTypeInitializer kNameToTypeInitializer;

}

ObjectType::ObjectType()
    : m_type(ObjectType::kUnknown)
{
}

ObjectType::ObjectType(ObjectType::TypeId type)
    : m_type(type)
{
    if (type < kUnknown || type >= kMaxObjectTypes) {
        m_type = kUnknown;
    }
}

ObjectType::ObjectType(const QString &typeName)
{
    auto it = kNameToType.find(typeName);
    if (it != kNameToType.end() && it.key() == typeName) {
        m_type = (TypeId)it.value();
    } else {
        m_type = kUnknown;
    }
}

const QString &ObjectType::getName() const
{
    if (m_type >= 0 && m_type < kMaxObjectTypes) {
        return kNames[m_type];
    }
    return kNames[kUnknown];
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
