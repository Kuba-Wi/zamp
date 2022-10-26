#pragma once

#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "LibInterface.hh"
#include "Scene.hh"

class ProgramInterpreter {
public:
    bool Read_XML_Config(const char* filename);
    bool ExecProgram(const char* filename);
    bool SendSceneState2Server() { return true; }

private:
    bool ExecPreprocesor(const char* filename, std::istringstream &outStream) const;

    std::map<std::string, std::unique_ptr<LibInterface>> LibManager_;
    int Socket2Serv_;
    Scene Scn_;
};
