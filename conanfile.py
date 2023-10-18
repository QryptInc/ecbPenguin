from conans import ConanFile, CMake, tools


class PenguinifyConan(ConanFile):
    name = "Penguinify"
    version = "1.0.0"
    license = "All Rights Reserved"
    author = "Qrypt Inc info@qrypt.com"
    description = "A tool to penguinify Bitmaps"
    topics = ("Qrypt", "ECB")
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package"
    requires = [
        "openssl/1.1.1g",
        "gtest/1.10.0"
    ]
    _cmake = None
    default_user = "Qrypt"
    default_channel = "test"

    def requirements(self):
        pass

    def configure(self):
        self.options['openssl'].shared = False

    def source(self):
        git = tools.Git(folder=self.source_folder)
        git.clone(
            "https://hard-carbon.visualstudio.com/Qrypt%20Open%20Source/_git/ECB_Penguin", "ecb_penguin")

    def _configure_cmake(self):
        if self._cmake is None:
            self._cmake = CMake(self)
            self._cmake.configure(source_folder=self.source_folder,
                                  build_folder=self.build_folder)
        return self._cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        pass
