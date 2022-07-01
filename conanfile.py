from conans import ConanFile, tools


class RiptideFileServerConan(ConanFile):
    name = "RiptideFileServer"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    description = "<Description of RiptideFileServer here>"
    url = "None"
    license = "None"
    author = "None"
    topics = None

    def package(self):
        self.copy("*")

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
