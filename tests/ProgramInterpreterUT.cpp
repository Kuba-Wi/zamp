#include <gtest/gtest.h>

#include "ProgramInterpreter.hh"

TEST(ProgramIntTest, ExecProgramShouldReturnTrueForCorrectCmdFile) {
    ProgramInterpreter pi;
    pi.Read_XML_Config("");
    ASSERT_TRUE(pi.ExecProgram("../../tests/input/interpreterTrueInput.cmd"));
}

TEST(ProgramIntTest, ExecProgramShouldReturnTrueForCmdFileWithWrongPlugin) {
    ProgramInterpreter pi;
    pi.Read_XML_Config("");
    ASSERT_TRUE(pi.ExecProgram("../../tests/input/interpNoPlugin.cmd"));
}

TEST(ProgramIntTest, ExecProgramShouldReturnFalseForWrongCmdFile) {
    ProgramInterpreter pi;
    pi.Read_XML_Config("");
    ASSERT_FALSE(pi.ExecProgram("../../tests/input/interpreterFalseInput.cmd"));
}

TEST(ProgramIntTest, ExecProgramShouldReturnFalseForWrongNameOfCmdFile) {
    ProgramInterpreter pi;
    pi.Read_XML_Config("");
    ASSERT_FALSE(pi.ExecProgram("some_name"));
}
