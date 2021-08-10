from conans import ConanFile, CMake, tools


class H5CppConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_find_package"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_mpi": [True, False],
        "with_boost": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "with_mpi": False,
        "with_boost": True,
        "hdf5:enable_cxx": False
    }

    def build_requirements(self):
        self.build_requires("gtest/1.11.0")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.with_mpi

    def configure(self):
        if self.options.get_safe("with_mpi", False):
            self.options["hdf5"].parallel = True

    def requirements(self):
        self.requires("hdf5/1.12.0")
        if self.options.with_boost:
            self.requires("boost/1.76.0")
        if self.options.get_safe("with_mpi", False):
            self.requires("openmpi/4.1.0")

    def build(self):
        cmake = CMake(self, generator="Ninja")
        cmake.definitions.update({
            "H5CPP_CONAN": "MANUAL",
            "H5CPP_WITH_MPI": self.options.get_safe("with_mpi", False),
            "H5CPP_WITH_BOOST": self.options.with_boost
        })
        cmake.configure()
        cmake.build()
        cmake.build(target="unit_tests")
