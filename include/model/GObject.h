//
// Created by 18224 on 2025/5/7.
//

#pragma once

#include "Object.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

class GObject : public Object {
public:

    /// 获取标志
    /// @return 标志
    int getFlags() const;

    /// 设置标志
    /// @param flags 标志
    void setFlags(int flags);

    /// 是否被选中
    /// @return 如果被选中，则返回true，否则返回false
    bool isSelected() const;

    /// 是否被移动
    /// @return 如果被移动，则返回true，否则返回false
    bool isMoving() const;

    /// 是否被修改
    /// @return 如果被修改，则返回true，否则返回false
    bool isModified() const;

    /// 是否可见
    /// @return 如果可见，则返回true，否则返回false
    bool isVisible() const;

    /// 是否固定
    /// @return 如果固定，则返回true，否则返回false
    bool isFixed() const;

    /// 设置选中状态
    /// @param selected 选中状态
    void setSelected(bool selected);

    /// 设置移动状态
    /// @param moving 移动状态
    void setMoving(bool moving);

    /// 设置修改状态
    /// @param modified 修改状态
    void setModified(bool modified);

    /// 设置可见状态
    /// @param visible 可见状态
    void setVisible(bool visible);

    /// 设置固定状态
    /// @param fixed 固定状态
    void setFixed(bool fixed);

};

}
}
}
