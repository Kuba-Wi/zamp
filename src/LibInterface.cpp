#include "LibInterface.hh"

#include <iostream>

#include <dlfcn.h>

LibInterface::LibInterface(std::string CmdName) : CmdName_{CmdName} {
    std::string libname = "libInterp4" + CmdName_ + ".so";
    LibHandler_ = dlopen(libname.c_str(), RTLD_LAZY);

    if (!LibHandler_) {
        std::cerr << "!!! " << libname << " not found" << std::endl;
        exit(0);
    }


    LibFun_ = dlsym(LibHandler_, "CreateCmd");
    if (!LibFun_) {
        std::cerr << "!!! CreateCmd not found" << std::endl;
        exit(0);
    }
    pCreateCmd_ = *reinterpret_cast<Interp4Command* (**)(void)>(&LibFun_);
}

LibInterface::~LibInterface() {
    dlclose(LibHandler_);
}
