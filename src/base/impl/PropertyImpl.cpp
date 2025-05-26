//
// Created by 18224 on 2025/5/7.
//

#include "PropertyImpl.h"
#include "MangoBDDataModel/util/Util.h"
#include <sstream>

using namespace mango::blockdiagram::datamodel;

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, bool value)
{
    if (!owner) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (name.isEmpty()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PropertyImpl* impl = new PropertyImpl(name, value);
    impl->setOwner(owner);
    owner->addProperty(impl);
    return impl;
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, int value)
{
    if (!owner) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (name.isEmpty()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PropertyImpl* impl = new PropertyImpl(name, value);
    impl->setOwner(owner);
    owner->addProperty(impl);
    return impl;
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, double value)
{
    if (!owner) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (name.isEmpty()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PropertyImpl* impl = new PropertyImpl(name, value);
    impl->setOwner(owner);
    owner->addProperty(impl);
    return impl;
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, const char *value)
{
    if (!owner) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (name.isEmpty()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (!value) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PropertyImpl* impl = new PropertyImpl(name, value);
    impl->setOwner(owner);
    owner->addProperty(impl);
    return impl;
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, const std::string &str)
{
    return New(owner, name, str.c_str());
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, ObjectImpl* value)
{
    if (!owner) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (name.isEmpty()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (!value) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PropertyImpl* impl = new PropertyImpl(name, value);
    impl->setOwner(owner);
    owner->addProperty(impl);
    return impl;
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, const QString& value)
{
    return New(owner, name, value.toStdString());
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, const QVector<bool> &vb)
{
    if (!owner) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (name.isEmpty()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PropertyImpl* impl = new PropertyImpl(name, vb);
    impl->setOwner(owner);
    owner->addProperty(impl);
    return impl;
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, const QVector<int> &vi)
{
    if (!owner) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (name.isEmpty()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PropertyImpl* impl = new PropertyImpl(name, vi);
    impl->setOwner(owner);
    owner->addProperty(impl);
    return impl;
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, const QVector<double> &vd)
{
    if (!owner) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (name.isEmpty()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PropertyImpl* impl = new PropertyImpl(name, vd);
    impl->setOwner(owner);
    owner->addProperty(impl);
    return impl;
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, const QList<QString>& ls)
{
    if (!owner) {
        // TODO: LOG_WARN
        return nullptr;
    }
    if (name.isEmpty()) {
        // TODO: LOG_WARN
        return nullptr;
    }
    PropertyImpl* impl = new PropertyImpl(name, ls);
    impl->setOwner(owner);
    owner->addProperty(impl);
    return impl;
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, std::initializer_list<bool> il)
{
    return New(owner, name, QVector<bool>(il));
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, std::initializer_list<int> il)
{
    return New(owner, name, QVector<int>(il));
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, std::initializer_list<double> il)
{
    return New(owner, name, QVector<double>(il));
}

PropertyImpl* PropertyImpl::New(ObjectImpl* owner, const QString& name, std::initializer_list<const char *> il)
{
    return New(owner, name, QList<QString>(il.begin(), il.end()));
}

PropertyImpl::PropertyImpl()
{
    m_type = PropType::UnKnown;
}

PropertyImpl::PropertyImpl(const QString& name, bool b)
{
    m_name = name;
    m_type = PropType::Bool;
    m_bool = b;
}

PropertyImpl::PropertyImpl(const QString& name, int i)
{
    m_name = name;
    m_type = PropType::Int;
    m_int = i;
}

PropertyImpl::PropertyImpl(const QString& name, double d)
{
    m_name = name;
    m_type = PropType::Double;
    m_double = d;
}

PropertyImpl::PropertyImpl(const QString& name, const char *str)
{
    m_name = name;
    m_type = PropType::String;
    if (!str) {
        m_array.len = 0;
        m_array.pointer = nullptr;
    } else {
        size_t len = strlen(str) + 1;
        m_array.len = static_cast<int>(len);
        m_array.pointer = Util::memAlloc(len);
        memcpy_s(m_array.pointer, len, str, len - 1);
        static_cast<char *>(m_array.pointer)[len - 1] = '\0';
    }
}

PropertyImpl::PropertyImpl(const QString& name, ObjectImpl *value)
{
    m_name = name;
    m_type = PropType::Object;
    m_array.pointer = value->clone(); // 内部使用new，对应的释放才能使用delete
}

PropertyImpl::PropertyImpl(const QString& name, const std::string &str) : PropertyImpl(name, str.c_str())
{
}

PropertyImpl::PropertyImpl(const QString& name, const QString &str) : PropertyImpl(name, str.toStdString())
{
}

PropertyImpl::PropertyImpl(const QString& name, const QVector<bool> &vb)
{
    m_name = name;
    m_type = PropType::BoolArray;
    constructContent(vb.data(), vb.size(), sizeof(bool));

    /// \note std::vector<bool> 可以考虑用位存储节省空间
}

PropertyImpl::PropertyImpl(const QString& name, const QVector<int> &vi)
{
    m_name = name;
    m_type = PropType::IntArray;
    constructContent(vi.data(), vi.size(), sizeof(int));
}

PropertyImpl::PropertyImpl(const QString& name, const QVector<double> &vd)
{
    m_type = PropType::DoubleArray;
    constructContent(vd.data(), vd.size(), sizeof(double));
}

PropertyImpl::PropertyImpl(const QString& name, const QList<QString> &ls)
{
    m_type = PropType::StringArray;
    m_array.len = static_cast<int>(ls.size());
    if (ls.empty()) {
        m_array.pointer = nullptr;
        return;
    }
    // 数组的每个元素都是PropertyImpl
    m_array.pointer = Util::memAlloc(ls.size() * sizeof(PropertyImpl));
    int i = 0;
    for (auto it = ls.cbegin(); it != ls.cend(); ++it) {
        auto pv = static_cast<PropertyImpl *>(m_array.pointer) + i;
        *pv = PropertyImpl("", *it);
        i++;
    }
}

PropertyImpl::PropertyImpl(const QString& name, std::initializer_list<bool> il) : PropertyImpl(name, QVector<bool>(il))
{
}

PropertyImpl::PropertyImpl(const QString& name, std::initializer_list<int> il) : PropertyImpl(name, QVector<int>(il))
{
}

PropertyImpl::PropertyImpl(const QString& name, std::initializer_list<double> il) : PropertyImpl(name, QVector<double>(il))
{
}

PropertyImpl::PropertyImpl(const QString& name, std::initializer_list<const char *> il)
    : PropertyImpl(name, QList<QString>{il.begin(), il.end()})
{
}

PropertyImpl::PropertyImpl(const PropertyImpl &props)
{
    operator=(props);
}

PropertyImpl::PropertyImpl(PropertyImpl &&props)
{
    operator=(std::move(props));
}

PropertyImpl::~PropertyImpl()
{
    freeContent();
}

PropertyImpl &PropertyImpl::operator=(const PropertyImpl &other)
{
    if (this == &other) {
        return *this;
    }
    m_name = other.m_name;
    m_type = other.m_type;
    m_owner = other.m_owner;
    switch (other.m_type) {
        case PropType::Bool:
            m_bool = other.m_bool;
            break;
        case PropType::Int:
            m_int = other.m_int;
            break;
        case PropType::Double:
            m_double = other.m_double;
            break;
        case PropType::Object: {
            freeContent();
            m_array.pointer = static_cast<ObjectImpl *>(other.m_array.pointer)->clone();
            break;
        }
        case PropType::String:
        case PropType::BoolArray:
        case PropType::IntArray:
        case PropType::DoubleArray: {
            freeContent();
            m_array.len = other.m_array.len;
            m_array.pointer = Util::memAlloc(other.m_array.len);
            memcpy_s(m_array.pointer, m_array.len, other.m_array.pointer, m_array.len);
            break;
        }
        case PropType::StringArray: {
            freeContent();
            m_array.len = other.m_array.len;
            m_array.pointer = Util::memAlloc(other.m_array.len * sizeof(PropertyImpl));
            for (quint32 i = 0; i < m_array.len; ++i) {
                PropertyImpl *this_prop = static_cast<PropertyImpl *>(m_array.pointer) + i;
                PropertyImpl *other_prop = static_cast<PropertyImpl *>(other.m_array.pointer) + i;

                this_prop->m_name = other_prop->m_name;
                this_prop->m_type = other_prop->m_type;
                this_prop->m_array.len = other_prop->m_array.len;
                this_prop->m_array.pointer = Util::memAlloc(other_prop->m_array.len);
                memcpy_s(this_prop->m_array.pointer, this_prop->m_array.len, other_prop->m_array.pointer, this_prop->m_array.len);
            }
            break;
        }
    }
    return *this;
}

PropertyImpl &PropertyImpl::operator=(PropertyImpl &&other)
{
    m_name = other.m_name;
    m_type = other.m_type;
    m_owner = other.m_owner;
    other.m_name.clear();
    other.m_type = PropType::UnKnown;
    other.m_owner = nullptr;

    switch (other.m_type) {
        case PropType::Bool:
            m_bool = other.m_bool;
            break;
        case PropType::Int:
            m_int = other.m_int;
            break;
        case PropType::Double:
            m_double = other.m_double;
            break;
        case PropType::String:
        case PropType::Object:
        case PropType::BoolArray:
        case PropType::IntArray:
        case PropType::DoubleArray:
        case PropType::StringArray: {
            m_array = other.m_array;
            other.m_array.pointer = nullptr;
            other.m_array.len = 0;
            break;
        }
    }
    return *this;
}

std::optional<bool> PropertyImpl::asBool() const
{
    if (m_type != PropType::Bool) {
        return std::nullopt;
    }
    return m_bool;
}

std::optional<int> PropertyImpl::asInt() const
{
    if (m_type!= PropType::Int) {
        return std::nullopt;
    }
    return m_int;
}

std::optional<double> PropertyImpl::asReal() const
{
    if (m_type!= PropType::Double) {
        return std::nullopt;
    }
    return m_double;
}

std::optional<QString> PropertyImpl::asString() const
{
    if (m_type!= PropType::String) {
        return std::nullopt;
    }
    if (m_array.len <= 1 || m_array.pointer == nullptr) {
        return QString();
    }
    return QString(static_cast<const char *>(m_array.pointer));
}

std::optional<ObjectImpl*> PropertyImpl::asObject() const
{
    if (m_type!= PropType::Object) {
        return std::nullopt;
    }
    if (m_array.pointer == nullptr) {
        return nullptr;
    }
    return static_cast<ObjectImpl*>(m_array.pointer);
}

std::optional<QVector<bool>> PropertyImpl::asBoolArray() const
{
    if (m_type!= PropType::BoolArray) {
        return std::nullopt;
    }
    QVector<bool> values;
    if (m_array.len <= 0 || m_array.pointer == nullptr) {
        return values;
    }
    for (quint32 i = 0; i < m_array.len; ++i) {
        bool value = *(static_cast<bool *>(m_array.pointer) + i);
        values.push_back(value);
    }
    return values;
}

std::optional<QVector<int>> PropertyImpl::asIntArray() const
{
    if (m_type!= PropType::IntArray) {
        return std::nullopt;
    }
    QVector<int> values;
    if (m_array.len <= 0 || m_array.pointer == nullptr) {
        return values;
    }
    for (quint32 i = 0; i < m_array.len; ++i) {
        int value = *(static_cast<int *>(m_array.pointer) + i);
        values.push_back(value);
    }
    return values;
}

std::optional<QVector<double>> PropertyImpl::asDoubleArray() const
{
    if (m_type!= PropType::DoubleArray) {
        return std::nullopt;
    }
    QVector<double> values;
    if (m_array.len <= 0 || m_array.pointer == nullptr) {
        return values;
    }
    for (quint32 i = 0; i < m_array.len; ++i) {
        double value = *(static_cast<double *>(m_array.pointer) + i);
        values.push_back(value);
    }
    return values;
}

std::optional<QList<QString>> PropertyImpl::asStringArray() const
{
    if (m_type!= PropType::StringArray) {
        return std::nullopt;
    }
    QList<QString> values;
    if (m_array.len <= 0 || m_array.pointer == nullptr) {
        return values;
    }
    for (quint32 i = 0; i < m_array.len; ++i) {
        PropertyImpl *prop = static_cast<PropertyImpl *>(m_array.pointer) + i;
        auto strValue = prop->asString();
        if (strValue.has_value()) {
            values.push_back(strValue.value());
        }
    }
    return values;
}

QString PropertyImpl::getValueString() const
{
    std::stringstream ss;
    switch (m_type) {
        case PropType::UnKnown:
            ss << "UnKnown";
            break;
        case PropType::Bool:
            ss << (m_bool ? "true" : "false");
            break;
        case PropType::Int:
            ss << m_int;
            break;
        case PropType::Double:
            ss << m_double;
            break;
        case PropType::String:
            ss << std::string(static_cast<const char *>(m_array.pointer), m_array.len - 1);
            break;
        case PropType::BoolArray: {
            for (quint32 i = 0; i < m_array.len; ++i) {
                bool bVal = *(static_cast<bool *>(m_array.pointer) + i);
                ss << (bVal ? "true" : "false");
                if (i != m_array.len - 1) {
                    ss << ", ";
                }
            }
            break;
        }
        case PropType::IntArray: {
            for (quint32 i = 0; i < m_array.len; ++i) {
                int iVal = *(static_cast<int *>(m_array.pointer) + i);
                ss << iVal;
                if (i != m_array.len - 1) {
                    ss << ", ";
                }
            }
            break;
        }
        case PropType::DoubleArray: {
            for (quint32 i = 0; i < m_array.len; ++i) {
                double dVal = *(static_cast<double *>(m_array.pointer) + i);
                ss << dVal;
                if (i != m_array.len - 1) {
                    ss << ", ";
                }
            }
            break;
        }
        case PropType::StringArray: {
            for (quint32 i = 0; i < m_array.len; ++i) {
                PropertyImpl *pv = static_cast<PropertyImpl *>(m_array.pointer) + i;
                ss << "`" << pv->getValueString().toStdString() << "`";
                if (i != m_array.len - 1) {
                    ss << ", ";
                }
            }
            break;
        }
    }
    return QString::fromStdString(ss.str());
}

QString PropertyImpl::printInfo() const
{
    std::stringstream ss;
    ss << m_name.toStdString() << ": " << getValueString().toStdString();

    switch (m_type) {
        case PropType::UnKnown: {
            ss << " [UnKnown]";
            break;
        }
        case PropType::Bool: {
            ss << " [Bool]";
            break;
        }
        case PropType::Int: {
            ss << " [Int]";
            break;
        }
        case PropType::Double: {
            ss << " [Double]";
            break;
        }
        case PropType::String: {
            ss << " [String]";
            break;
        }
        case PropType::Object: {
            ss << " [" << static_cast<ObjectImpl *>(m_array.pointer)->getObjectType().getName().toStdString() << "]";
            break;
        }
        case PropType::BoolArray: {
            ss << " [BoolArray]";
            break;
        }
        case PropType::IntArray: {
            ss << " [IntArray]";
            break;
        }
        case PropType::DoubleArray: {
            ss << " [DoubleArray]";
            break;
        }
        case PropType::StringArray: {
            ss << " [StringArray]";
            break;
        }
    }
    return QString::fromStdString(ss.str());
}

void PropertyImpl::constructContent(const void *data, size_t valuesLen, size_t valueSize)
{
    if (!data) {
        m_array.len = 0;
        m_array.pointer = nullptr;
        return;
    }
    m_array.len = static_cast<int>(valuesLen);
    m_array.pointer = nullptr;
    if (valuesLen > 0) {
        int totalSize = static_cast<int>(valuesLen * valueSize);
        m_array.pointer = Util::memAlloc(totalSize);
        memcpy_s(m_array.pointer, totalSize, data, totalSize);
    }
}

void PropertyImpl::freeContent()
{
    if (!m_array.pointer) {
        return;
    }
    switch (m_type) {
        case PropType::Object: {
            delete m_array.pointer;
            m_array.pointer = nullptr;
            m_array.len = 0;
            break;
        }
        case PropType::String:
        case PropType::BoolArray:
        case PropType::IntArray:
        case PropType::DoubleArray: {
            Util::memFree(m_array.pointer);
            m_array.pointer = nullptr;
            m_array.len = 0;
            break;
        }
        case PropType::StringArray: {
            for (quint32 i = 0; i < m_array.len; ++i) {
                PropertyImpl *prop = static_cast<PropertyImpl *>(m_array.pointer) + i;
                if (prop->m_array.pointer) {
                    Util::memFree(prop->m_array.pointer);
                    prop->m_array.pointer = nullptr;
                }
            }
            Util::memFree(m_array.pointer);
            m_array.pointer = nullptr;
            break;
        }
    }
}