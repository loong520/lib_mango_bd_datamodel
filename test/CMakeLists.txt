# cmake统一使用3.12版本，可兼容Visual Studio 2017和CLion两种开发环境
cmake_minimum_required(VERSION 3.12)

# 库名称，版本号
project(mangobddatamodel-test
        LANGUAGES CXX
        VERSION "1.0.0")

# 载入公共宏和函数
include($ENV{CBB_HOME}/cmake_modules/Common.cmake)

# 初始化Qt5工程.
use_qt5_for_test(Core Gui)

# 定义到处库符号
add_definitions(-DMANGO_BD_DATAMODEL_EXPORTS)

# 生成库的链接名称(LINK_NAME)
gen_link_name_for_test()

# 引入第三方库的头文件目录
include_directories(../thirdparty/doctest/include)

# 引入本项目的头文件目录
include_directories(.)
include_directories(../include)
include_directories(../include/MangoBDDataModel)
include_directories(../include/MangoBDDataModel/base)
include_directories(../include/MangoBDDataModel/model)
include_directories(../include/MangoBDDataModel/style)

# 引入本项目的源文件目录
aux_source_directory(. DIR_SRC)
aux_source_directory(../src DIR_SRC)
aux_source_directory(../src/base DIR_SRC)
aux_source_directory(../src/base/impl DIR_SRC)
aux_source_directory(../src/common DIR_SRC)
aux_source_directory(../src/model DIR_SRC)
aux_source_directory(../src/model/impl DIR_SRC)
aux_source_directory(../src/style DIR_SRC)
aux_source_directory(../src/style/impl DIR_SRC)
aux_source_directory(../src/utils DIR_SRC)

# 编译选项配置
if (CMAKE_HOST_WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

add_executable(${LINK_NAME_FOR_TEST} ${DIR_SRC})

target_precompile_headers(${LINK_NAME_FOR_TEST} PRIVATE <QtCore>)

# 链接Qt5动态库
link_qt5_for_test()

# 链接要测试的动态库
#link_lib_for_test()