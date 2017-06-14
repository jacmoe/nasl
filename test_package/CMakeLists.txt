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

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/memsharded/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES nasl/0.4@jacmoe/testing
                BASIC_SETUP
                BUILD missing)

include_directories(
    ${CONAN_INCLUDE_DIRS_NASL}/include
    ${CONAN_INCLUDE_DIRS_NASL}/3rd/include
    ${CONAN_INCLUDE_DIRS}
)

add_executable(example main.c)
target_link_libraries(example
    ${CONAN_LIBS}
)
set_property(TARGET example PROPERTY C_STANDARD 99) # 90 99 11
