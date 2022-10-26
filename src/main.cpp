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
#include "ProgramInterpreter.hh"

using namespace std;

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
  ProgramInterpreter pi;
  pi.Read_XML_Config("");
  pi.ExecProgram("../opis_dzialan.cmd");
}
