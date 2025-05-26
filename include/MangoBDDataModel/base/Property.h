//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/base/Object.h"
#include <optional>

namespace mango {
namespace blockdiagram {
namespace datamodel {

class MANGO_BD_DATAMODEL_API Property : public Object {
public:
    static Property* New(Object* owner, const QString& name, bool value);
    static Property* New(Object* owner, const QString& name, int value);
    static Property* New(Object* owner, const QString& name, double value);
    static Property* New(Object* owner, const QString& name, const char *value);
    static Property* New(Object* owner, const QString& name, const std::string &str);
    static Property* New(Object* owner, const QString& name, const QString& value);
    static Property* New(Object* owner, const QString& name, const QVector<bool> &vb);
    static Property* New(Object* owner, const QString& name, const QVector<int> &vi);
    static Property* New(Object* owner, const QString& name, const QVector<double> &vd);
    static Property* New(Object* owner, const QString& name, const QList<QString>& ls);
    static Property* New(Object* owner, const QString& name, std::initializer_list<bool> il);
    static Property* New(Object* owner, const QString& name, std::initializer_list<int> il);
    static Property* New(Object* owner, const QString& name, std::initializer_list<double> il);
    static Property* New(Object* owner, const QString& name, std::initializer_list<const char *> il);
    static Property* New(Object* owner, const QString& name, Object* value); // 必须实现value的clone函数（Property内部使用clone进行深拷贝）
    
    /// 获取bool值
    /// @return 具体值的可选类型，如果属性值的类型不匹配，则返回空的可选类型
    std::optional<bool> asBool() const;

    /// 获取int值
    /// @return 具体值的可选类型，如果属性值的类型不匹配，则返回空的可选类型
    std::optional<int> asInt() const;

    /// 获取double值
    /// @return 具体值的可选类型，如果属性值的类型不匹配，则返回空的可选类型
    std::optional<double> asReal() const;

    /// 获取QString值
    /// @return 具体值的可选类型，如果属性值的类型不匹配，则返回空的可选类型
    std::optional<QString> asString() const;

    /// 获取Object*值
    /// @return 具体值的可选类型，如果属性值的类型不匹配，则返回空的可选类型
    std::optional<Object*> asObject() const;

    /// 获取QVector<bool>值
    /// @return 具体值的可选类型，如果属性值的类型不匹配，则返回空的可选类型
    std::optional<QVector<bool>> asBoolArray() const;

    /// 获取QVector<int>值
    /// @return 具体值的可选类型，如果属性值的类型不匹配，则返回空的可选类型
    std::optional<QVector<int>> asIntArray() const;

    /// 获取QVector<double>值
    /// @return 具体值的可选类型，如果属性值的类型不匹配，则返回空的可选类型
    std::optional<QVector<double>> asDoubleArray() const;

    /// 获取QList<QString>值
    /// @return 具体值的可选类型，如果属性值的类型不匹配，则返回空的可选类型
    std::optional<QList<QString>> asStringArray() const;

    /// 获取属性名称
    /// @return 属性名称
    QString getName() const;

    /// 获取所有者对象
    /// @return 所有者对象指针
    Object* getOwner() const;

    /// 获取属性值的字符串表示
    /// @return 属性值的字符串表示
    QString getValueString() const;

    /// 打印信息
    /// @return 包含属性信息的字符串
    QString printInfo() const;
};

}
}
}