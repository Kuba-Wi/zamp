#include <gtest/gtest.h>

#include "CommunicationFake.hh"
#include "Interp4Pause.hh"

TEST(PauseTest, getCmdNameShouldReturnCommandName) {
    Interp4Pause ip;
    ASSERT_STREQ(ip.GetCmdName(), "Pause");
}

TEST(PauseTest, readParamsShouldReturnTrueWhenCorrectInput) {
    Interp4Pause ip;
    std::istream str{std::istringstream{"23\n"}.rdbuf()};
    ASSERT_TRUE(ip.ReadParams(str));
}

TEST(PauseTest, execCmdShouldReturnTrueWhenNoMobileObj) {
    Interp4Pause ip;
    CommunicationFake com_fake;
    Scene scn;
    ASSERT_TRUE(ip.ExecCmd(scn, com_fake));
}

struct PauseFalseTest : ::testing::Test, ::testing::WithParamInterface<const char*> {};

INSTANTIATE_TEST_CASE_P(TestsWithFalseResult,
                        PauseFalseTest,
                        ::testing::Values("Ob_A\n",
                                          ""));

TEST_P(PauseFalseTest, readParamsShouldReturnFalseWhenWrongInput) {
    Interp4Pause ip;
    std::istream str{std::istringstream{GetParam()}.rdbuf()};
    ASSERT_FALSE(ip.ReadParams(str));
}
