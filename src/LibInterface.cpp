#include "LibInterface.hh"

#include <iostream>

#include <dlfcn.h>

LibInterface::LibInterface(LibInterface&& other) {
    CmdName_ = other.CmdName_;
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

bool LibInterface::createCmdBuilder() {
    std::string libname = "libInterp4" + CmdName_ + ".so";
    LibHandler_ = dlopen(libname.c_str(), RTLD_LAZY);

    if (!LibHandler_) {
        std::cerr << "!!! " << libname << " not found" << std::endl;
        return false;
    }

    void* LibFun = dlsym(LibHandler_, "CreateCmd");
    if (!LibFun) {
        std::cerr << "!!! CreateCmd not found" << std::endl;
        return false;
    }
    pCreateCmd_ = reinterpret_cast<Interp4Command* (*)(void)>(LibFun);

    return true;
}

std::unique_ptr<Interp4Command> LibInterface::createCmd() {
    if (pCreateCmd_) {
        return std::unique_ptr<Interp4Command>(pCreateCmd_());
    }
    return nullptr;
}
