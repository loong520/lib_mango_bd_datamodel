//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/base/Property.h"
#include "ObjectImpl.h"
#include <optional>

namespace mango {
namespace blockdiagram {
namespace datamodel {

class PropertyImpl : public ObjectImpl {
public:
    PropertyImpl();
    PropertyImpl(const QString& name, bool value);
    PropertyImpl(const QString& name, int value);
    PropertyImpl(const QString& name, double value);
    PropertyImpl(const QString& name, const char * value);
    PropertyImpl(const QString& name, const std::string &str);
    PropertyImpl(const QString& name, const QString& value);
    PropertyImpl(const QString& name, const QVector<bool> &vb);
    PropertyImpl(const QString& name, const QVector<int> &vi);
    PropertyImpl(const QString& name, const QVector<double> &vd);
    PropertyImpl(const QString& name, const QList<QString>& ls);
    PropertyImpl(const QString& name, std::initializer_list<bool> il);
    PropertyImpl(const QString& name, std::initializer_list<int> il);
    PropertyImpl(const QString& name, std::initializer_list<double> il);
    PropertyImpl(const QString& name, std::initializer_list<const char *> il);

    PropertyImpl(const PropertyImpl &props);
    PropertyImpl(PropertyImpl &&props);
    ~PropertyImpl();
    PropertyImpl &operator=(const PropertyImpl &);
    PropertyImpl &operator=(PropertyImpl &&);

    // 获取具体值
    std::optional<bool> asBool() const;
    std::optional<int> asInt() const;
    std::optional<double> asReal() const;
    std::optional<QString> asString() const;
    std::optional<QVector<bool>> asBoolArray() const;
    std::optional<QVector<int>> asIntArray() const;
    std::optional<QVector<double>> asDoubleArray() const;
    std::optional<QList<QString>> asStringArray() const;

    // 打印属性信息
    QString printString() const;


    QString getName() const;

    Object* getOwner() const;

    QString getValueString() const;

private:
    // 构建属性值的内容
    void constructContent(const void *data, size_t valuesLen, size_t valueSize);

    // 释放属性值的内存
    void freeContent();

public:
    QString m_name;
    PropType m_type;
    union {
        bool    m_bool;
        int     m_int;
        double  m_double;
        struct Array {
            void *pointer;          // 数组地址（字符串数组时是指针数组）
            quint32 len;            // 数组长度
        } m_array = {nullptr, 0};
    };
};

}
}
}