#include "ProgramInterpreter.hh"

int main()
{
  Communication com;
  ProgramInterpreter pi{com};
  pi.Read_XML_Config("../config/config.xml", "../config/config.xsd");
  pi.ExecProgram("../opis_dzialan.cmd");
}
