#pragma once

#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

#include "Communication.hh"
#include "Configuration.hh"
#include "LibInterface.hh"
#include "Scene.hh"

class ProgramInterpreter {
public:
    ProgramInterpreter(Communication& com) : communication_{com} {}
    bool Read_XML_Config(const char* filename, const char* grammar_file);
    bool ExecProgram(const char* filename);
    bool SendSceneState2Server() { return true; }

private:
    void BuildConfigurationCommand(std::string& command);
    bool ExecPreprocesor(const char* filename, std::istringstream &outStream) const;
    void AddObjectsToScene();
    void CreateInterpCommands();
    bool CreateInterpCommand(const std::string& libname);
    void RemoveInterpCommand(const std::string& libname);

    std::map<std::string, std::unique_ptr<LibInterface>> LibManager_;
    Scene Scn_;
    Configuration config_;
    Communication& communication_;
    std::list<std::thread> threads_list_;
};
