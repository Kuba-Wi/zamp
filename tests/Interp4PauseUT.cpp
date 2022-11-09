#include <gtest/gtest.h>

#include "Interp4Pause.hh"

TEST(PauseTest, getCmdNameShouldReturnCommandName) {
    Interp4Pause im;
    ASSERT_STREQ(im.GetCmdName(), "Pause");
}

TEST(PauseTest, readParamsShouldReturnTrueWhenCorrectInput) {
    Interp4Pause im;
    std::istream str{std::istringstream{"23\n"}.rdbuf()};
    ASSERT_TRUE(im.ReadParams(str));
}

TEST(PauseTest, execCmdShouldReturnTrueWhenCorrectInput) {
    Interp4Pause im;
    std::istream str{std::istringstream{"Ob_A 123 90\n"}.rdbuf()};
    ASSERT_TRUE(im.ExecCmd(nullptr, 0));
}

struct PauseFalseTest : ::testing::Test, ::testing::WithParamInterface<const char*> {};

INSTANTIATE_TEST_CASE_P(TestsWithFalseResult,
                        PauseFalseTest,
                        ::testing::Values("Ob_A\n",
                                          ""));

TEST_P(PauseFalseTest, readParamsShouldReturnFalseWhenWrongInput) {
    Interp4Pause im;
    std::istream str{std::istringstream{GetParam()}.rdbuf()};
    ASSERT_FALSE(im.ReadParams(str));
}
