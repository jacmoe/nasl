from conans import ConanFile, CMake, tools
import os


class NaslConan(ConanFile):
    name = "nasl"
    version = "0.2"
    license = "BSD 2-Clause License"
    url = "https://github.com/jacmoe/nasl"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "nasl/*"

    def source(self):
        tools.replace_in_file("nasl/CMakeLists.txt", "project(nasl_lib)", '''project(nasl_lib)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()''')

    def build(self):
        cmake = CMake(self)
        shared = "-DBUILD_SHARED_LIBS=ON" if self.options.shared else ""
        self.run('cmake nasl %s %s' % (cmake.command_line, shared))
        self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="nasl")
        self.copy("*nasl.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["nasl"]
