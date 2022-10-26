#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>

#include <dlfcn.h>

#include "Interp4Command.hh"
#include "LibInterface.hh"
#include "MobileObj.hh"

using namespace std;

bool ExecPreprocesor(const char* filename, istringstream &IStrm4Cmds) {
  constexpr size_t LINE_SIZE = 500;
  char Line[LINE_SIZE];
  string Cmd4Preproc = "cpp -P ";
  ostringstream OTmpStrm;
  Cmd4Preproc += filename;
  FILE* pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc) {
    return false;
  }

  while (fgets(Line, LINE_SIZE, pProc)) {
    OTmpStrm << Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}

void printInterp4Commands(const std::unique_ptr<Interp4Command>& command_ptr) {
  cout << endl;
  cout << command_ptr->GetCmdName() << endl;
  cout << endl;
  command_ptr->PrintSyntax();
  cout << endl;
  command_ptr->PrintCmd();
  cout << endl;
}

int main()
{
  istringstream stream;
  if (!ExecPreprocesor("../opis_dzialan.cmd", stream)) {
    return 0;
  }

  std::map<std::string, std::unique_ptr<LibInterface>> interfaceMap;
  interfaceMap[{"Move"}] = std::make_unique<LibInterface>(LibInterface{"Move"});
  interfaceMap[{"Set"}] = std::make_unique<LibInterface>(LibInterface{"Set"});
  interfaceMap[{"Rotate"}] = std::make_unique<LibInterface>(LibInterface{"Rotate"});
  interfaceMap[{"Pause"}] = std::make_unique<LibInterface>(LibInterface{"Pause"});

  std::string plugin_name;
  while (stream >> plugin_name) {
    if (interfaceMap.find(plugin_name) == interfaceMap.end()) {
      std::cout << "No plugin named: " << plugin_name << std::endl;
      return 0;
    }

    auto cmd_ptr = interfaceMap[plugin_name]->createCmd();
    if(!cmd_ptr->ReadParams(stream)) {
      std::cout << "Error in reading parameters of plugin " << plugin_name << std::endl;
      return 0;
    }
    cmd_ptr->PrintCmd();
    cmd_ptr->ExecCmd(nullptr, 0);
  }
}
