#pragma once

#include <memory>
#include <string>

#include "Interp4Command.hh"

class LibInterface {
public:
    LibInterface(const char* CmdName);
    LibInterface(const LibInterface&) = delete;
    LibInterface(LibInterface&& other);
    ~LibInterface();

    std::unique_ptr<Interp4Command> createCmd() { return std::unique_ptr<Interp4Command>(pCreateCmd_()); }
    const char* GetCmdName() const { return CmdName_.c_str(); }
private:
    void* LibHandler_ = nullptr;
    std::string CmdName_;
    Interp4Command* (*pCreateCmd_)(void);
};
