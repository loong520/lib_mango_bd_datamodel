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
    void destory() override;

    // 边界框
    virtual QRectF getBoundingRect() const;

public:
    quint32 m_flags = 0;
    int     m_rotation = 0;
    int     m_zValue = 0;
    QPointF m_pos;
    QRectF  m_boundingRect;
};

}
}
}
