#include <gtest/gtest.h>

#include "CommunicationFake.hh"
#include "Interp4Move.hh"

TEST(MoveTest, getCmdNameShouldReturnCommandName) {
    Interp4Move im;
    ASSERT_STREQ(im.GetCmdName(), "Move");
}

TEST(MoveTest, readParamsShouldReturnTrueWhenCorrectInput) {
    Interp4Move im;
    std::istream str{std::istringstream{"Ob_A 123 90\n"}.rdbuf()};
    ASSERT_TRUE(im.ReadParams(str));
}

TEST(MoveTest, execCmdShouldReturnFalseWhenNoMobileObj) {
    Interp4Move im;
    CommunicationFake com_fake;
    Scene scn;
    ASSERT_FALSE(im.ExecCmd(scn, com_fake));
}

TEST(MoveTest, execCmdShouldReturnTrueForCorrectMobileObj) {
    Interp4Move im;
    CommunicationFake com_fake;
    Scene scn;
    std::istream str{std::istringstream{"Ob_A 123 9\n"}.rdbuf()};
    im.ReadParams(str);
    scn.AddMobileObj("Ob_A");
    ASSERT_TRUE(im.ExecCmd(scn, com_fake));
}

struct MoveFalseTest : ::testing::Test, ::testing::WithParamInterface<const char*> {};

INSTANTIATE_TEST_CASE_P(TestsWithFalseResult,
                        MoveFalseTest,
                        ::testing::Values("Ob_A 123\n",
                                          "1 2\n" 
                                          "xd\n",
                                          "",
                                          "Ob_A 12 xd\n",
                                          "Ob_A xd 12\n"));

TEST_P(MoveFalseTest, readParamsShouldReturnFalseWhenWrongInput) {
    Interp4Move im;
    std::istream str{std::istringstream{GetParam()}.rdbuf()};
    ASSERT_FALSE(im.ReadParams(str));
}
