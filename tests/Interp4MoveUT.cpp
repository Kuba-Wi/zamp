#include <gtest/gtest.h>

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

TEST(MoveTest, execCmdShouldReturnTrueWhenCorrectInput) {
    Interp4Move im;
    std::istream str{std::istringstream{"Ob_A 123 90\n"}.rdbuf()};
    ASSERT_TRUE(im.ExecCmd(nullptr, 0));
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

TEST_P(MoveFalseTest, readParamsShouldReturnFalseWhenCorrectInput) {
    Interp4Move im;
    std::istream str{std::istringstream{GetParam()}.rdbuf()};
    ASSERT_FALSE(im.ReadParams(str));
}
