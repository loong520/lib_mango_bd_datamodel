//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "PinImpl.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class CompositePinImpl : public PinImpl {
public:
    ObjectType getObjectType() const override { return ObjectType::kCompositePin; }
    bool isTypeOf(const ObjectType& type) const override;
    void Delete() override;

public:
    QList<PinImpl*> m_innerPins;
};

}
}
}