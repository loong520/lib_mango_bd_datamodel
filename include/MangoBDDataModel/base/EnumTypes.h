//
// Created by Administrator on 2025/5/25.
//

#pragma once

#include "MangoBDDataModel/base/Config.h"

namespace mango {
namespace blockdiagram {
namespace datamodel {

enum MANGO_BD_DATAMODEL_API GObjectFlag {
    ObjectIsSelected = 0x1,
    ObjectIsMoving = 0x2,
    ObjectIsModified = 0x4,
    ObjectIsVisible = 0x8,
    ObjectIsFixed = 0x10,
};

enum MANGO_BD_DATAMODEL_API LabelType {
    LabelForMainName,
    LabelForComment,
};

enum MANGO_BD_DATAMODEL_API ConnectMode {
    ConnectModeFly = 0, // 飞线
    ConnectModeNamed,   // 命名连线
    ConnectModeDirect,  // 直接连线
};

enum MANGO_BD_DATAMODEL_API Direction {
    Bottom = 0,
    Top = 1,
    Left = 2,
    Right = 3,
    Middle = 4,
};

enum MANGO_BD_DATAMODEL_API PinShape {
    Line = 0,
    Inverted,
    Clock,
    InvertedClock,
    InputLow,
    ClockLow,
    OutputLow,
    FallingEdgeClock,
    NonLogic,

    LastOption = NonLogic, ///< this is the sentinel value, must be set to last enum value
    Inherit
};

/// 定义图元外观的改变程度
enum MANGO_BD_DATAMODEL_API GObjectUpdateFlags {
    None        = 0x00,     ///< 无需更新
    Appearance  = 0x01,     ///< 可见性标志已更改
    Color       = 0x02,     ///< 颜色已经改变
    Geometry    = 0x04,     ///< 位置或形状已发生变化
    Layers      = 0x08,     ///< 图层已更改
    Initial_Add = 0x10,     ///< 项目正在添加到视图中
    Repaint     = 0x20,     ///< 物品需要重新绘制
    All         = 0xef      ///< 除了 Initial_Add 之外的所有内容
};

enum class MANGO_BD_DATAMODEL_API PropType {
    UnKnown = 0,
    Bool,
    Int,
    Double,
    String,
    Object,

    /** array containing int, real, string or groups */
    BoolArray,
    IntArray,
    DoubleArray,
    StringArray,
    ObjectArray,
};


}
}
}
