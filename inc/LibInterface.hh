#pragma once

#include <string>

#include "Interp4Command.hh"

class LibInterface {
public:
    LibInterface(const char* CmdName);
    ~LibInterface();
    Interp4Command* createCmd() { return pCreateCmd_(); }   //TODO: return unique_ptr or shared_ptr
private:
    void* LibHandler_;
    void* LibFun_;
    std::string CmdName_;
    Interp4Command* (*pCreateCmd_)(void);
};
