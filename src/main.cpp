#include <iostream>
#include <cassert>
#include <cstdio>
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


int main()
{
  // void *pLibHnd_Move = dlopen("libInterp4Move.so", RTLD_LAZY);
  // Interp4Command *(*pCreateCmd_Move)(void);
  // void *pFun;

  // if (!pLibHnd_Move) {
  //   cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
  //   return 1;
  // }


  // pFun = dlsym(pLibHnd_Move, "CreateCmd");
  // if (!pFun) {
  //   cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  //   return 1;
  // }
  // pCreateCmd_Move = reinterpret_cast<Interp4Command* (*)(void)>(pFun);


  // Interp4Command *pCmd = pCreateCmd_Move();

  // cout << endl;
  // cout << pCmd->GetCmdName() << endl;
  // cout << endl;
  // pCmd->PrintSyntax();
  // cout << endl;
  // pCmd->PrintCmd();
  // cout << endl;
  
  // delete pCmd;

  // dlclose(pLibHnd_Move);

  istringstream stream;
  if (ExecPreprocesor("../opis_dzialan.cmd", stream)) {
    std::cout << stream.str();
  }

  std::map<std::string, std::unique_ptr<LibInterface>> interfaceMap;
  interfaceMap[{"Move"}] = std::make_unique<LibInterface>(LibInterface{"Move"});

  std::unique_ptr<Interp4Command> ptr = interfaceMap["Move"]->createCmd();
  cout << endl;
  cout << ptr->GetCmdName() << endl;
  cout << endl;
  ptr->PrintSyntax();
  cout << endl;
  ptr->PrintCmd();
  cout << endl;
}
