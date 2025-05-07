//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "ObjectImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class GObjectImpl : public ObjectImpl {
public:

    ObjectType getObjectType() const override { return ObjectType::kGObject; }
    bool isTypeOf(const ObjectType& type) const override;

    void destory();

    void setFlags(int flags);
    int getFlags() const;

    bool isSelected() const;
    bool isMoving() const;
    bool isModified() const;
    bool isVisible() const;
    bool isFixed() const;

    void setSelected(bool selected);
    void setMoving(bool moving);
    void setModified(bool modified);
    void setVisible(bool visible);
    void setFixed(bool fixed);

public:
    quint32 m_flags = 0;

};

}
}
}
