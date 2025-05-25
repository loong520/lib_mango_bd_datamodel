//
// Created by 18224 on 2025/5/7.
//

#include "LabelImpl.h"

using namespace mango::blockdiagram::datamodel;

LabelImpl* LabelImpl::New(GraphElementImpl* parent)
{
    if (parent == nullptr) {
        // TODO: LOG_WARN
        return nullptr;
    }
    LabelImpl* impl = new LabelImpl((Object*)parent);
    parent->addLabel(impl);

    return impl;
}

LabelImpl::LabelImpl(const LabelImpl& other) : GraphElementImpl(other)
{
    m_text = other.m_text;
    m_type = other.m_type;
}

LabelImpl* LabelImpl::clone() const
{
    return new LabelImpl(*this);
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
    if (!m_parent) {
        // TODO: LOG_ERROR
        return;
    }
    auto ptr = dynamic_cast<GraphElementImpl*>((ObjectImpl*)m_parent);
    if (ptr) {
        obj_impl_ptr(GraphElement, m_parent)->removeLabel(this);
        return;
    } else {
        // TODO: LOG_ERROR
        return;
    }
}

QRectF LabelImpl::getBoundingRect() const
{
    return QRectF();
}

bool LabelImpl::hitTest(const QPointF &aPosition, int aAccuracy) const
{
    return false;
}

bool LabelImpl::hitTest(const QRectF &aRect, bool aContained, int aAccuracy) const
{
    return false;
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