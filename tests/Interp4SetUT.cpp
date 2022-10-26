#include <gtest/gtest.h>

#include "Interp4Set.hh"

TEST(SetTest, getCmdNameShouldReturnCommandName) {
    Interp4Set im;
    ASSERT_STREQ(im.GetCmdName(), "Set");
}

TEST(SetTest, readParamsShouldReturnTrueWhenCorrectInput) {
    Interp4Set im;
    std::istream str{std::istringstream{"Ob_A 23 123 90\n"}.rdbuf()};
    ASSERT_TRUE(im.ReadParams(str));
}

TEST(SetTest, execCmdShouldReturnTrueWhenCorrectInput) {
    Interp4Set im;
    std::istream str{std::istringstream{"Ob_A 123 90\n"}.rdbuf()};
    ASSERT_TRUE(im.ExecCmd(nullptr, 0));
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

TEST_P(SetFalseTest, readParamsShouldReturnFalseWhenCorrectInput) {
    Interp4Set im;
    std::istream str{std::istringstream{GetParam()}.rdbuf()};
    ASSERT_FALSE(im.ReadParams(str));
}
