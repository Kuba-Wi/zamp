#include <gtest/gtest.h>

#include "CommunicationFake.hh"
#include "Interp4Rotate.hh"

TEST(RotateTest, getCmdNameShouldReturnCommandName) {
    Interp4Rotate ir;
    ASSERT_STREQ(ir.GetCmdName(), "Rotate");
}

TEST(RotateTest, readParamsShouldReturnTrueWhenCorrectInput) {
    Interp4Rotate ir;
    std::istream str{std::istringstream{"Ob_A 23 123\n"}.rdbuf()};
    ASSERT_TRUE(ir.ReadParams(str));
}

TEST(RotateTest, execCmdShouldReturnFalseWhenNoMobileObj) {
    Interp4Rotate ir;
    CommunicationFake com_fake;
    Scene scn;
    ASSERT_FALSE(ir.ExecCmd(scn, com_fake));
}

TEST(MoveTest, execCmdShouldReturnTrueForCorrectMobileObj) {
    Interp4Rotate ir;
    CommunicationFake com_fake;
    Scene scn;
    std::istream str{std::istringstream{"Ob_A 123 9\n"}.rdbuf()};
    ir.ReadParams(str);
    scn.AddMobileObj("Ob_A");
    ASSERT_TRUE(ir.ExecCmd(scn, com_fake));
}

struct RotateFalseTest : ::testing::Test, ::testing::WithParamInterface<const char*> {};

INSTANTIATE_TEST_CASE_P(TestsWithFalseResult,
                        RotateFalseTest,
                        ::testing::Values("Ob_A 123\n",
                                          "1 2\n" 
                                          "xd\n",
                                          "",
                                          "Ob_A 12 xd\n",
                                          "Ob_A xd 12\n"));

TEST_P(RotateFalseTest, readParamsShouldReturnFalseWhenWrongInput) {
    Interp4Rotate ir;
    std::istream str{std::istringstream{GetParam()}.rdbuf()};
    ASSERT_FALSE(ir.ReadParams(str));
}
