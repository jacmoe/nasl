#
#   This file is part of the
# ███╗   ██╗ █████╗ ███████╗██╗     
# ████╗  ██║██╔══██╗██╔════╝██║     
# ██╔██╗ ██║███████║███████╗██║     
# ██║╚██╗██║██╔══██║╚════██║██║     
# ██║ ╚████║██║  ██║███████║███████╗
# ╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚══════╝
#   project : https://github.com/jacmoe/nasl
#
#   Copyright 2017 Jacob Moen
#
#
cmake_minimum_required(VERSION 2.8.12)
project(nasl)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

include(CMakeToolsHelpers OPTIONAL)


# Dependencies
# ------------

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)

find_package(GLEW 1.10)
if(${GLEW_FOUND})
  add_definitions(-DUSE_GLEW)
endif()

# Paths
# -----

set(SRCDIR "./src")
set(SHADERDIR "./shaders")
set(THIRDPARTY "./src/3rd")

# Main target build
# -----------------

set(TARGET_NAME nasl)

set(Sources
    #${SRCDIR}/defs.h
)


set(3rdParty_Headers
    ${THIRDPARTY}/my_basic.h
    ${THIRDPARTY}/nuklear.h
    ${THIRDPARTY}/nuklear_glfw_gl3.h
    ${THIRDPARTY}/stb_image.h
)

set(3rdParty_Source
    ${THIRDPARTY}/my_basic.c
)

add_executable(${TARGET_NAME}
    ${SRCDIR}/main.c
    ${Sources}
    ${3rdParty_Headers}
    ${3rdParty_Source}
)

set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 99) # 90 99 11
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")

include_directories(
    ${SRCDIR}
    ${THIRDPARTY}
    ${GLFW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(${TARGET_NAME}
    ${GLFW_STATIC_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)
