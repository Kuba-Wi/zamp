#include <gtest/gtest.h>

#include "LibInterface.hh"

TEST(LibInterfaceTest, getCmdNameShouldReturnMove) {
    LibInterface li{"Move"};
    ASSERT_STREQ(li.GetCmdName(), "Move");
}

TEST(LibInterfaceTest, createCmdShouldCreateInterp4ComandForMove) {
    LibInterface li{"Move"};
    std::unique_ptr<Interp4Command> interpCmdPtr = li.createCmd();
    ASSERT_STREQ(interpCmdPtr->GetCmdName(), "Move");
}

TEST(LibInterfaceTest, moveContructorShouldMoveMemberObjects) {
    LibInterface li{"Move"};
    LibInterface liMoved = std::move(li);
    ASSERT_EQ(li.createCmd(), nullptr);

    std::unique_ptr<Interp4Command> interpCmdPtr = liMoved.createCmd();
    ASSERT_STREQ(interpCmdPtr->GetCmdName(), "Move");
}

TEST(LibInterfaceTest, getCmdNameShouldReturnSet) {
    LibInterface li{"Set"};
    ASSERT_STREQ(li.GetCmdName(), "Set");
}

TEST(LibInterfaceTest, createCmdShouldCreateInterp4ComandForSet) {
    LibInterface li{"Set"};
    std::unique_ptr<Interp4Command> interpCmdPtr = li.createCmd();
    ASSERT_STREQ(interpCmdPtr->GetCmdName(), "Set");
}
