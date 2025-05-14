//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "ObjectType.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

#if defined(impl_ptr)
    #undef impl_ptr
#endif
#define impl_ptr(OBJECT) ((OBJECT##Impl*)this)

#if defined(obj_impl_ptr)
    #undef obj_impl_ptr
#endif
#define obj_impl_ptr(OBJECT, PTR) ((OBJECT##Impl*)PTR)

using DBID = quint64;
class Property;

class MANGO_BD_DATAMODEL_API Object {
public:
    /// 获取对象类型
    /// @return 对象类型
    ObjectType getObjectType() const;

    /// 检查是否是指定类型的对象
    /// @param type 要检查的类型
    /// @return 如果是指定类型的对象，则返回true，否则返回false
    bool isTypeOf(const ObjectType& type) const;

    /// 获取对象的dbid
    /// @return 对象的dbid
    DBID getDbid() const;

    /// 检查对象是否存活. 存活的对象是指没有被删除或者释放的对象.
    /// @return 如果对象存活，则返回true，否则返回false
    bool isAlive();

    /// 删除对象
    void Delete();

    /// 获取父对象
    /// @return 父对象指针
    Object* getParent() const;

    /// 检查对象是否有属性
    /// @return 如果对象有属性，则返回true，否则返回false
    bool hasProperty() const;

    /// 添加属性
    /// @param property 要添加的属性指针
    void addProperty(Property* property);

    /// 移除属性
    /// @param property 要移除的属性名称
    void deleteProperty(const QString& name);

    /// 通过属性名查找属性
    /// @param name 属性名
    /// @return 找到的属性指针，如果未找到则返回nullptr
    Property* findProperty(const QString& name) const;

    /// 获取所有属性
    /// @return 所有属性的指针列表
    QList<Property *> getProperties() const;

    Object() = delete;
    Object(const Object&) = delete;
//    ~Object() = delete;
    Object& operator=(const Object&) = delete;
};

} // end of namespace datamodel
} // end of namespace blockdiagram
} // end of namespace mango
