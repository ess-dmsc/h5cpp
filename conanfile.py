from conans import ConanFile, CMake


class H5CppConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "gcc", "txt"
    options = {
        "with_mpi": [True, False],
        "with_boost": [True, False]
    }
    default_options = {
        "with_mpi": False,
        "with_boost": True,
        "hdf5:enable_cxx": False
    }

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
        if self.options.with_mpi:
            self.requires("openmpi/4.1.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
