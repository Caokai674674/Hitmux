cmake_minimum_required(VERSION 3.13)

if (CMAKE_HOST_UNIX)
    set(CMAKE_SYSTEM_NAME Windows)
    set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
    # cross compilers to use for C, C++ and RC
    set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
    set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

    # modify default behavior of FIND_XXX() commands
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(PKG_CONFIG_EXECUTABLE ${TOOLCHAIN_PREFIX}-pkg-config)
endif ()

project(ege-demos LANGUAGES CXX)

add_library(ege-common INTERFACE)
target_include_directories(ege-common INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

message(STATUS "ege include dir: ${CMAKE_CURRENT_SOURCE_DIR}/include")

# 设置静态库搜索路径
if (MSVC)
    # 设置 MSVC 编译选项, 当版本大于 vs2019 时, 使用 c++17 标准.
    set(CPP_COMPILE_OPTIONS "/std:c++17")

    if (MSVC_VERSION GREATER_EQUAL 1930)
        # vs2022 以上, 静态库是兼容的.
        if (CMAKE_CL_64)
            set(osLibDir "vs2022/x64")
        else ()
            set(osLibDir "vs2022/x86")
        endif ()
    elseif (MSVC_VERSION GREATER_EQUAL 1920)
        # vs2019 以上, 静态库是兼容的.
        if (CMAKE_CL_64)
            set(osLibDir "vs2019/x64")
        else ()
            set(osLibDir "vs2019/x86")
        endif ()
    elseif (MSVC_VERSION GREATER_EQUAL 1910)
        # vs2017
        if (CMAKE_CL_64)
            set(osLibDir "vs2017/x64")
        else ()
            set(osLibDir "vs2017/x86")
        endif ()
        # 设置 MSVC 编译选项, 当版本为 vs2017 时, 使用 c++14 标准.
        set(CPP_COMPILE_OPTIONS "/std:c++14")
    elseif (MSVC_VERSION GREATER_EQUAL 1900)
        # vs2015
        if (CMAKE_CL_64)
            set(osLibDir "vs2015/amd64")
        else ()
            set(osLibDir "vs2015")
        endif ()
        # 设置 MSVC 编译选项, 当版本为 vs2015 时, 使用 c++14 标准.
        set(CPP_COMPILE_OPTIONS "/std:c++14")
    elseif (MSVC_VERSION GREATER_EQUAL 1600)

        if (MSVC_VERSION GREATER_EQUAL 1700)
            message(WARNING "You are using vs2012/vs2013, which is not tested, please use vs2010, vs2015 or later version of MSVC compiler.")
        endif ()

        # vs2010
        if (CMAKE_CL_64)
            set(osLibDir "vs2010/amd64")
        else ()
            set(osLibDir "vs2010")
        endif ()

    else ()
        message(FATAL_ERROR "你的 MSVC 版本太老了, 请使用 vs2015 或更新版本的 MSVC 编译器. 与时俱进吧, 不要一直使用十年前的编译器.")
    endif ()

    target_compile_options(ege-common INTERFACE /source-charset:utf-8 /MP ${CPP_COMPILE_OPTIONS} /D_USE_MATH_DEFINES /D__STDC_LIMIT_MACROS "$<$<CONFIG:DEBUG>:/DDEBUG>" "$<$<CONFIG:RELEASE>:/DNDEBUG>" "$<$<CONFIG:RELWITHDEBINFO>:/DNDEBUG>" "$<$<CONFIG:MINSIZEREL>:/DNDEBUG>" "$<IF:$<CONFIG:Debug>,/MDd,/MD>")
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if (CMAKE_HOST_APPLE)
        set(osLibDir "macOS")
    else ()
        set(osLibDir "mingw-w64-debian")
    endif ()
    target_compile_options(ege-common INTERFACE -D_FORTIFY_SOURCE=0)
    target_link_options(ege-common INTERFACE -mwindows -static -static-libgcc -static-libstdc++)
    target_link_libraries(ege-common INTERFACE graphics gdiplus gdi32 imm32 msimg32 ole32 oleaut32 winmm uuid)
endif ()

if (DEFINED osLibDir)
    message(STATUS "ege library dir: ${CMAKE_CURRENT_SOURCE_DIR}/lib/${osLibDir}")
    target_link_directories(ege-common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/${osLibDir})
endif ()


file(GLOB DEMO_SRCS
        LIST_DIRECTORIES false
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/demo/*.cpp")

message(STATUS "DEMO_SRCS: ${DEMO_SRCS}")

add_custom_target(demos)

foreach (DEMO_SRC ${DEMO_SRCS})
    message(STATUS "DEMO_SRC: ${DEMO_SRC}")
    get_filename_component(DEMO_NAME ${DEMO_SRC} NAME_WE)
    add_executable(${DEMO_NAME} ${DEMO_SRC})
    target_link_libraries(${DEMO_NAME} ege-common)
    add_dependencies(demos ${DEMO_NAME})
endforeach ()

target_sources(egerotateimage PRIVATE demo/egelogo.rc)

message(CHECK_START "Finding GMP Library")
find_library(gmp gmp QUIET)
if (gmp)
    message(CHECK_PASS "found")
    file(
            GLOB GMP_DEMO_SRCS
            LIST_DIRECTORIES false
            CONFIGURE_DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/demo/gmp-demo/*.cpp"
    )
    foreach (GMP_DEMO_SRC ${GMP_DEMO_SRCS})
        message(STATUS "GMP_DEMO_SRC: ${GMP_DEMO_SRC}")
        get_filename_component(DEMO_NAME ${GMP_DEMO_SRC} NAME_WE)
        add_executable(${DEMO_NAME} ${GMP_DEMO_SRC})
        target_link_libraries(${DEMO_NAME} gmp ege-common)
        target_link_libraries(${DEMO_NAME} gmp)
        add_dependencies(demos ${DEMO_NAME})
    endforeach ()
else ()
    message(CHECK_PASS "not found")
endif ()
