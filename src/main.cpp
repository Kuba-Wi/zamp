#include "ProgramInterpreter.hh"

int main()
{
  ProgramInterpreter pi;
  pi.Read_XML_Config("../config/config.xml");
  pi.ExecProgram("../opis_dzialan.cmd");
}
