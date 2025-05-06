cmake_minimum_required(VERSION 3.12)
project(XuanWu LANGUAGES CXX VERSION "1.0.0")

# 可执行程序名字
macro(gen_link_name_for_app)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(LINK_NAME "${PROJECT_NAME}-d")
    else ()
        set(LINK_NAME "${PROJECT_NAME}")
    endif ()
endmacro()

macro(gen_link_name_for_lib)
    if (CMAKE_HOST_WIN32)
        set(LINK_NAME "lib${PROJECT_NAME}-${PROJECT_VERSION}")
    else ()
        set(LINK_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
    endif ()

    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(LINK_NAME "${LINK_NAME}-d")
    endif ()

    set(LIB_FOR_TEST ${LINK_NAME} CACHE INTERNAL "lib for test")
endmacro()

macro(gen_link_name_for_test)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(LINK_NAME_FOR_TEST "${PROJECT_NAME}-d")
    else ()
        set(LINK_NAME_FOR_TEST "${PROJECT_NAME}")
    endif ()
endmacro()

macro(use_qt5)
    if (NOT DEFINED CMAKE_BUILD_TYPE)
        MESSAGE(FATAL_ERROR "CMAKE_BUILD_TYPE not defined! It must be defined as 'Debug' or 'Release'!")
    endif ()

    set(CMAKE_SKIP_BUILD_RPATH ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_STANDARD 17)

    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    set(QT5_COMPONENTS ${ARGN} CACHE INTERNAL "qt5 components")

    foreach (COMP IN LISTS QT5_COMPONENTS)
        find_package(QT NAMES Qt5 COMPONENTS ${COMP} REQUIRED)
        find_package(Qt5 COMPONENTS ${COMP} REQUIRED)
    endforeach ()
endmacro()
macro(link_qt5)
    foreach (COMP IN LISTS QT5_COMPONENTS)
        if (LINK_NAME)
            target_link_libraries(${LINK_NAME} PRIVATE Qt5::${COMP})
        else ()
            target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::${COMP})
        endif ()
    endforeach ()
endmacro()

macro(use_qt5_for_test)
    if (NOT DEFINED CMAKE_BUILD_TYPE)
        message(FATAL_ERROR "CMAKE_BUILD_TYPE not defined! It must be defined as 'Debug' or 'Release'!")
    endif ()

    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_STANDARD 17)

    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    set(QT5_COMPONENTS ${ARGN} CACHE INTERNAL "qt5 components for tests")

    foreach (COMP IN LISTS QT5_COMPONENTS_FOR_TEST)
        find_package(QT NAMES Qt5 COMPONENTS ${COMP} REQUIRED)
        find_package(Qt5 COMPONENTS ${COMP} REQUIRED)
    endforeach ()
endmacro()
macro(link_qt5_for_test)
    foreach (COMP IN LISTS QT5_COMPONENTS_FOR_TEST)
        if (LINK_NAME)
            target_link_libraries(${LINK_NAME_FOR_TEST} PRIVATE Qt5::${COMP})
        else ()
            target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::${COMP})
        endif ()
    endforeach ()
endmacro()

macro(link_lib_for_test)
    if (LIB_FOR_TEST)
        if (LINK_NAME_FOR_TEST)
            if (CMAKE_HOST_WIN32)
                target_link_libraries(${LINK_NAME_FOR_TEST} PRIVATE ${LIB_FOR_TEST})
            else ()
                target_link_libraries(${LINK_NAME_FOR_TEST} PRIVATE ${LIB_FOR_TEST})
            endif ()
        endif ()
    endif ()
endmacro()

use_qt5(Core Gui WebChannel WebEngineWidgets)
gen_link_name_for_app()

include_directories(src)
include_directories(src/utils)
include_directories(src/webBridge)
include_directories(src/widgets)

aux_source_directory(src DIR_SRC)
aux_source_directory(src/utils DIR_SRC)
aux_source_directory(src/webBridge DIR_SRC)
aux_source_directory(src/widgets DIR_SRC)

# 编译选项配置
if (CMAKE_HOST_WIN32)
    add_compile_options("/Zi")
    add_compile_options("/DEBUG")
endif ()
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

if (CMAKE_HOST_WIN32)
    message(STATUS "current os is windows")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin_win)
else ()
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
        message(STATUS "current os is linux of aarch64")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin_arm)
    else ()
        message(STATUS "current os is linux of x86_64")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin_linux)
    endif ()
endif ()

add_executable(
    ${LINK_NAME}
    ${DIR_SRC}
)
target_precompile_headers(
    ${LINK_NAME}
    PRIVATE
    <QtCore>
    <QtGui>
    <QtWidgets>
)

#链接Qt5动态库
link_qt5()

if (WIN32)
    target_link_libraries(${LINK_NAME} PRIVATE netapi32)
endif ()