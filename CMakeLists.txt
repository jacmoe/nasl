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

include(CMakeToolsHelpers OPTIONAL)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

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

set(SHADERDIR "./shaders")

# Main target build
# -----------------

set(TARGET_NAME nasl_test)

include_directories(
    nasl/include
    nasl/3rd/include
    ${GLFW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

add_subdirectory(nasl)

add_executable(${TARGET_NAME}
    test.c
)

set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 99) # 90 99 11
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")

target_link_libraries(${TARGET_NAME}
    nasl
    ${GLFW_STATIC_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)
