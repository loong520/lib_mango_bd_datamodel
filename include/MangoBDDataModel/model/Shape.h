//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "MangoBDDataModel/model/GObject.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class GraphElement;

class MANGO_BD_DATAMODEL_API Shape : public GObject {
public:
    /// 创建一个新的图形对象
    /// \param parent 父对象
    /// \return 新的图形对象
    static Shape *New(GraphElement *parent);

    /// 克隆对象
    /// \return 克隆的对象指针
    Shape *clone() const;

    /// 增加一个子图形
    /// \param shape 子图形
    void addSubShape(GObject *shape);

    /// 删除一个子图形
    /// \param shape 子图形
    void removeSubShape(GObject *shape);

    /// 获取子图形
    /// \return 子图形
    QList<GObject *> getSubShapes() const;

    /// shape是否为空
    /// \return
    bool isEmpty() const;
};

}
}
}