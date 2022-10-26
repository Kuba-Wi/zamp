#include "ProgramInterpreter.hh"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

bool ProgramInterpreter::Read_XML_Config(const char* filename) {
    LibManager_[{"Move"}] = std::make_unique<LibInterface>(LibInterface{"Move"});
    LibManager_[{"Set"}] = std::make_unique<LibInterface>(LibInterface{"Set"});
    LibManager_[{"Rotate"}] = std::make_unique<LibInterface>(LibInterface{"Rotate"});
    LibManager_[{"Pause"}] = std::make_unique<LibInterface>(LibInterface{"Pause"});

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
