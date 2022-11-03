#include "ProgramInterpreter.hh"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

bool ProgramInterpreter::Read_XML_Config(const char* filename) {
    if (!CreateInterpCommand("Move")) {
        RemoveInterpCommand("Move");
        return false;
    }

    if (!CreateInterpCommand("Set")) {
        RemoveInterpCommand("Set");
        return false;
    }

    if (!CreateInterpCommand("Rotate")) {
        RemoveInterpCommand("Rotate");
        return false;
    }

    if (!CreateInterpCommand("Pause")) {
        RemoveInterpCommand("Pause");
        return false;
    }

    return true;
}

bool ProgramInterpreter::ExecProgram(const char* filename) {
    std::istringstream cmdStream;
    if (!ExecPreprocesor(filename, cmdStream)) {
        return false;
    }

    std::string plugin_name;
    while (cmdStream >> plugin_name) {
        if (LibManager_.find(plugin_name) == LibManager_.end()) {
            std::cout << "No plugin named: " << plugin_name << std::endl;
            return true;
        }

        auto cmd_ptr = LibManager_[plugin_name]->createCmd();
        if (!cmd_ptr) {
            std::cout << "Error: plugin " << plugin_name << " does not exist" << std::endl;
            return true;
        }

        if(!cmd_ptr->ReadParams(cmdStream)) {
            std::cout << "Error in reading parameters of plugin " << plugin_name << std::endl;
            return false;
        }
        cmd_ptr->PrintCmd();
        cmd_ptr->ExecCmd(nullptr, 0);
    }

    return true;
}

bool ProgramInterpreter::ExecPreprocesor(const char* filename, std::istringstream &outStream) const {
    constexpr size_t LINE_SIZE = 500;
    char Line[LINE_SIZE];
    std::string Cmd4Preproc = "cpp -P ";
    std::ostringstream OTmpStrm;
    Cmd4Preproc += filename;
    FILE* pProc = popen(Cmd4Preproc.c_str(), "r");

    if (!pProc) {
        return false;
    }

    while (fgets(Line, LINE_SIZE, pProc)) {
        OTmpStrm << Line;
    }
    outStream.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}

bool ProgramInterpreter::CreateInterpCommand(const std::string& libname) {
    LibManager_[libname] = std::make_unique<LibInterface>(LibInterface{libname});
    return LibManager_[libname]->createCmdBuilder();
}

void ProgramInterpreter::RemoveInterpCommand(const std::string& libname) {
    auto it = LibManager_.find(libname);
    if (it != LibManager_.end()) {
        LibManager_.erase(it);
    }
}
