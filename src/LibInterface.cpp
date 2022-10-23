#include "LibInterface.hh"

#include <iostream>

#include <dlfcn.h>

LibInterface::LibInterface(const char* CmdName) : CmdName_{CmdName} {
    std::string libname = "libInterp4" + CmdName_ + ".so";
    LibHandler_ = dlopen(libname.c_str(), RTLD_LAZY);

    if (!LibHandler_) {
        std::cerr << "!!! " << libname << " not found" << std::endl;
        exit(0);
    }

    void* LibFun = dlsym(LibHandler_, "CreateCmd");
    if (!LibFun) {
        std::cerr << "!!! CreateCmd not found" << std::endl;
        exit(0);
    }
    pCreateCmd_ = reinterpret_cast<Interp4Command* (*)(void)>(LibFun);
}

LibInterface::LibInterface(LibInterface&& other) {
    LibHandler_ = other.LibHandler_;
    other.LibHandler_ = nullptr;
    pCreateCmd_ = other.pCreateCmd_;
    other.pCreateCmd_ = nullptr;
}

LibInterface::~LibInterface() {
    if (LibHandler_) {
        dlclose(LibHandler_);
    }
}

std::unique_ptr<Interp4Command> LibInterface::createCmd() {
    if (pCreateCmd_) {
        return std::unique_ptr<Interp4Command>(pCreateCmd_());
    }
    return nullptr;
}
