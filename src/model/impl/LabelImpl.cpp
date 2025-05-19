//
// Created by 18224 on 2025/5/7.
//

#include "LabelImpl.h"

using namespace mango::blockdiagram::datamodel;

Label* LabelImpl::New(GraphElement* parent)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    LabelImpl* impl = new LabelImpl((Object*)parent);
    obj_impl_ptr(GraphElement, parent)->addLabel(impl);

    return (Label*)impl;
}

LabelImpl::LabelImpl(Object* parent) : GraphElementImpl(parent)
{
}

bool LabelImpl::isTypeOf(const ObjectType& type) const
{
    auto typeId = type.getType();
    if (typeId == ObjectType::kObject ||
        typeId == ObjectType::kGObject ||
        typeId == ObjectType::kGraphElement ||
        typeId == ObjectType::kLabel) {
        return true;
    }
    return false;
}

void LabelImpl::Delete()
{

}

QRectF LabelImpl::getBoundingRect() const
{
    return QRectF();
}

void LabelImpl::setText(const QString& text)
{
    m_text = text;
}

QString LabelImpl::getText() const
{
    return m_text;
}

void LabelImpl::setType(LabelType type)
{
    m_type = type;
}

LabelType LabelImpl::getType() const
{
    return m_type;
}