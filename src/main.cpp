#include "ProgramInterpreter.hh"

int main(int argc, char** argv)
{
  if (argc < 3) {
    std::cout << "Needed 2 arguments to start. First is an XML, second is a command file\n";
    return 0;
  }

  Communication com;
  ProgramInterpreter pi{com};
  pi.Read_XML_Config(argv[1], "../config/config.xsd");
  pi.ExecProgram(argv[2]);
}
