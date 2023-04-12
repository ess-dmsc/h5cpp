from conan import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.env import VirtualBuildEnv, VirtualRunEnv


class H5CppConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
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
        "hdf5/*:hl": True,
        "hdf5/*:enable_cxx": False,
        "hdf5/*:shared": False
    }

    def build_requirements(self):
        self.build_requires("catch2/3.3.2")
        # self.build_requires("catch2/2.13.10")
        self.build_requires("ninja/1.10.2")
        self.build_requires("zlib/1.2.13")
        # self.build_requires("cmake/3.25.3")
        if self.settings.os == "Windows":
            self.build_requires("hdf5/1.14.0")
            # self.build_requires("hdf5/1.12.2")
            self.build_requires("libiconv/1.17")
            self.build_requires("szip/2.1.1")
            self.build_requires("bzip2/1.0.8")
            if self.options.get_safe("with_boost", False):
                self.build_requires("boost/1.81.0")
            if self.options.get_safe("with_mpi", False):
                self.build_requires("openmpi/4.1.0")


    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.with_mpi

    def configure(self):
        if self.options.get_safe("with_mpi", False):
            self.options["hdf5"].parallel = True

    def requirements(self):
        # self.requires("hdf5/1.12.2")
        self.requires("hdf5/1.14.0")
        self.requires("catch2/3.3.2")
        # self.requires("catch2/2.13.10")
        self.requires("libiconv/1.17")
        self.requires("zlib/1.2.13")
        self.requires("szip/2.1.1")
        self.requires("bzip2/1.0.8")

        if self.options.get_safe("with_boost", False):
            if self.settings.os == "Windows":
                self.requires("boost/1.81.0")
            elif self.settings.os == "Macos":
                self.requires("boost/1.81.0")
            else:
                self.requires("boost/1.81.0")
        if self.options.get_safe("with_mpi", False):
            self.requires("openmpi/4.1.0")

    def build(self):
        cmake = CMake(self)
        build_env = VirtualBuildEnv(self).vars()
        run_env = VirtualRunEnv(self).vars()
        with build_env.apply():
            with run_env.apply():
                cmake.configure(variables={
                    "H5CPP_CONAN": "MANUAL",
                    "H5CPP_WITH_MPI": self.options.get_safe("with_mpi", False),
                    "H5CPP_WITH_BOOST": self.options.get_safe("with_boost", False)})
                cmake.build()
