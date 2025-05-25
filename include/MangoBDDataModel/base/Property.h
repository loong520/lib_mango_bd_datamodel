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

    /// 获取属性所属对象
    /// @return 属性所属对象指针
    Object* getOwner() const;

    /// 获取属性值的字符串表示
    /// @return 属性值的字符串表示
    QString getValueString() const;
};

}
}
}