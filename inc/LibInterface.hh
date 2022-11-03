#pragma once

#include <memory>
#include <string>

#include "Interp4Command.hh"

class LibInterface {
public:
    LibInterface(const std::string& CmdName) : CmdName_{CmdName} {}
    LibInterface(const LibInterface&) = delete;
    LibInterface(LibInterface&& other);
    ~LibInterface();

    bool createCmdBuilder();
    std::unique_ptr<Interp4Command> createCmd();
private:
    void* LibHandler_ = nullptr;
    std::string CmdName_;
    Interp4Command* (*pCreateCmd_)(void) = nullptr;
};
