#include <gtest/gtest.h>

#include "Interp4Move.hh"

TEST(MoveTest, getCmdNameShouldReturnCommandName) {
    Interp4Move im;
    ASSERT_STREQ(im.GetCmdName(), "Move");
}
