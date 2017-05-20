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
project(PackageTest)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)

find_package(OpenGL REQUIRED)

find_package(GLEW 1.10)
if(${GLEW_FOUND})
  add_definitions(-DUSE_GLEW)
endif()

include_directories(
    ${CONAN_INCLUDE_DIRS_NASL}/include
    ${CONAN_INCLUDE_DIRS_NASL}/3rd/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

add_executable(example main.c)
target_link_libraries(example
    ${CONAN_LIBS}
    m
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

# CTest is a testing tool that can be used to test your project.
# enable_testing()
# add_test(NAME example
#          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#          COMMAND example)
