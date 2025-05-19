//
// Created by 18224 on 2025/5/7.
//

#include "MangoBDDataModel/model/Label.h"
#include "impl/LabelImpl.h"
#include "impl/GraphElementImpl.h"

using namespace mango::blockdiagram::datamodel;

Label* Label::New(GraphElement* parent)
{
    return LabelImpl::New(parent);
}

void Label::setText(const QString& text)
{
    impl_ptr(Label)->setText(text);
}

QString Label::getText() const
{
    return impl_ptr(Label)->m_text;
}

void Label::setType(LabelType type)
{
    impl_ptr(Label)->setType(type);
}

LabelType Label::getType() const
{
    return impl_ptr(Label)->m_type;
}