//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include <QMap>

#include "MangoBDDataModel/base/Object.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class ObjectImpl {
public:
    ObjectImpl(Object *parent = nullptr);

    virtual ~ObjectImpl();

    virtual ObjectType getObjectType() const
    {
        return ObjectType::kObject;
    }

    virtual bool isTypeOf(const ObjectType& type) const;

    virtual void Delete();

    DBID getDbid() const;

    bool isAlive();

    Object* getParent() const;
    void setParent(Object* parent);

    bool hasProperty() const;

    void addProperty(Property* property);

    void deleteProperty(const QString& name);

    Property* findProperty(const QString& name) const;

    QList<Property*> getProperties() const;

public:
    Object* m_parent = nullptr;
    QMap<QString, Property*> *m_props = nullptr;
};

} // end of namespace datamodel
} // end of namespace blockdiagram
} // end of namespace mango
