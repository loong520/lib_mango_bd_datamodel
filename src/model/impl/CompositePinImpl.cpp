//
// Created by 18224 on 2025/5/7.
//

#include "CompositePinImpl.h"
#include "NodeImpl.h"

using namespace mango::blockdiagram::datamodel;

bool CompositePinImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kPin ||
        typeId == ObjectType::kCompositePin) {
        return true;
    }
    return false;
}

void CompositePinImpl::Delete()
{
    if (!m_parent) {
        // TODO: LOG_ERROR
        return;
    }
    ObjectType::TypeId typeId = m_parent->getObjectType();
    if (typeId == ObjectType::kNode) {
        obj_impl_ptr(Node, m_parent)->removeGraphElement(this);
    } else {
        // TODO: LOG_ERROR
    }
}