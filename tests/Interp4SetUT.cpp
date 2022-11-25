#include <gtest/gtest.h>

#include <mutex>

#include "CommunicationFake.hh"
#include "Interp4Set.hh"
#include "Scene.hh"

TEST(SetTest, getCmdNameShouldReturnCommandName) {
    Interp4Set is;
    ASSERT_STREQ(is.GetCmdName(), "Set");
}

TEST(SetTest, readParamsShouldReturnTrueWhenCorrectInput) {
    Interp4Set is;
    std::istream str{std::istringstream{"Ob_A 23 123 90\n"}.rdbuf()};
    ASSERT_TRUE(is.ReadParams(str));
}

TEST(SetTest, execCmdShouldReturnFalseWhenNoMobileObj) {
    Interp4Set is;
    CommunicationFake fake_com;
    Scene scn;
    ASSERT_FALSE(is.ExecCmd(scn, fake_com));
}

TEST(MoveTest, execCmdShouldReturnTrueForCorrectMobileObj) {
    Interp4Set is;
    CommunicationFake com_fake;
    Scene scn;
    std::istream str{std::istringstream{"Ob_A 23 123 90\n"}.rdbuf()};
    is.ReadParams(str);
    scn.AddMobileObj("Ob_A");
    ASSERT_TRUE(is.ExecCmd(scn, com_fake));
}

struct SetFalseTest : ::testing::Test, ::testing::WithParamInterface<const char*> {};

INSTANTIATE_TEST_CASE_P(TestsWithFalseResult,
                        SetFalseTest,
                        ::testing::Values("Ob_A 123 12\n",
                                          "1 2 3\n" 
                                          "xd\n",
                                          "",
                                          "Ob_A 12 11 xd\n",
                                          "Ob_A xd 12 11\n"));

TEST_P(SetFalseTest, readParamsShouldReturnFalseWhenWrongInput) {
    Interp4Set is;
    std::istream str{std::istringstream{GetParam()}.rdbuf()};
    ASSERT_FALSE(is.ReadParams(str));
}
