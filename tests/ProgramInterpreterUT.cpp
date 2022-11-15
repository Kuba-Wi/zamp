#include <gtest/gtest.h>

#include "CommunicationFake.hh"
#include "ProgramInterpreter.hh"

TEST(ProgramIntTest, ExecProgramShouldReturnTrueForCorrectCmdFile) {
    CommunicationFake com;
    ProgramInterpreter pi{com};
    pi.Read_XML_Config("../../tests/input/input.xml", "../../tests/input/config.xsd");
    ASSERT_TRUE(pi.ExecProgram("../../tests/input/interpreterTrueInput.cmd"));
}

TEST(ProgramIntTest, ExecProgramShouldReturnTrueForCorrectCmdFileAndNoXML) {
    CommunicationFake com;
    ProgramInterpreter pi{com};
    pi.Read_XML_Config("", "");
    ASSERT_TRUE(pi.ExecProgram("../../tests/input/interpreterTrueInput.cmd"));
}

TEST(ProgramIntTest, ExecProgramShouldReturnTrueForCmdFileWithWrongPlugin) {
    CommunicationFake com;
    ProgramInterpreter pi{com};
    pi.Read_XML_Config("../../tests/input/input.xml", "../../tests/input/config.xsd");
    ASSERT_TRUE(pi.ExecProgram("../../tests/input/interpNoPlugin.cmd"));
}

TEST(ProgramIntTest, ExecProgramShouldReturnTrueForWrongCmdFileAndNoXML) {
    CommunicationFake com;
    ProgramInterpreter pi{com};
    pi.Read_XML_Config("", "");
    ASSERT_TRUE(pi.ExecProgram("../../tests/input/interpreterFalseInput.cmd"));
}

TEST(ProgramIntTest, ExecProgramShouldReturnFalseForWrongCmdFile) {
    CommunicationFake com;
    ProgramInterpreter pi{com};
    pi.Read_XML_Config("../../tests/input/input.xml", "../../tests/input/config.xsd");
    ASSERT_FALSE(pi.ExecProgram("../../tests/input/interpreterFalseInput.cmd"));
}

TEST(ProgramIntTest, ExecProgramShouldReturnFalseForWrongNameOfCmdFile) {
    CommunicationFake com;
    ProgramInterpreter pi{com};
    pi.Read_XML_Config("../../tests/input/input.xml", "../../tests/input/config.xsd");
    ASSERT_FALSE(pi.ExecProgram("some_name"));
}
