#include <gtest/gtest.h>

#include "Interp4Rotate.hh"

TEST(RotateTest, getCmdNameShouldReturnCommandName) {
    Interp4Rotate im;
    ASSERT_STREQ(im.GetCmdName(), "Rotate");
}

TEST(RotateTest, readParamsShouldReturnTrueWhenCorrectInput) {
    Interp4Rotate im;
    std::istream str{std::istringstream{"Ob_A 23 123\n"}.rdbuf()};
    ASSERT_TRUE(im.ReadParams(str));
}

TEST(RotateTest, execCmdShouldReturnTrueWhenCorrectInput) {
    Interp4Rotate im;
    std::istream str{std::istringstream{"Ob_A 123 90\n"}.rdbuf()};
    ASSERT_TRUE(im.ExecCmd(nullptr, 0));
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

TEST_P(RotateFalseTest, readParamsShouldReturnFalseWhenCorrectInput) {
    Interp4Rotate im;
    std::istream str{std::istringstream{GetParam()}.rdbuf()};
    ASSERT_FALSE(im.ReadParams(str));
}
