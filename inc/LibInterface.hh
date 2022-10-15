#pragma once

#include <string>

#include "Interp4Command.hh"

class LibInterface {
public:
    LibInterface(std::string CmdName);
    ~LibInterface();
    Interp4Command* createCmd() { return pCreateCmd_(); }
private:
    void* LibHandler_;
    void* LibFun_;
    std::string CmdName_;
    Interp4Command* (*pCreateCmd_)(void);
};
