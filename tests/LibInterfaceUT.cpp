#include <gtest/gtest.h>

#include "LibInterface.hh"

TEST(LibInterfaceTest, createCmdBuilderShouldFailForWrongLibname) {
    LibInterface li{"XD"};
    ASSERT_FALSE(li.createCmdBuilder());
}

TEST(LibInterfaceTest, createCmdShouldCreateInterp4ComandForMove) {
    LibInterface li{"Move"};
    li.createCmdBuilder();
    std::unique_ptr<Interp4Command> interpCmdPtr = li.createCmd();
    ASSERT_NE(interpCmdPtr, nullptr);
    ASSERT_STREQ(interpCmdPtr->GetCmdName(), "Move");
}

TEST(LibInterfaceTest, moveContructorShouldMoveMemberObjects) {
    LibInterface li{"Move"};
    li.createCmdBuilder();
    LibInterface liMoved = std::move(li);
    ASSERT_EQ(li.createCmd(), nullptr);

    std::unique_ptr<Interp4Command> interpCmdPtr = liMoved.createCmd();
    ASSERT_NE(interpCmdPtr, nullptr);
    ASSERT_STREQ(interpCmdPtr->GetCmdName(), "Move");
}

TEST(LibInterfaceTest, createCmdShouldCreateInterp4ComandForSet) {
    LibInterface li{"Set"};
    li.createCmdBuilder();
    std::unique_ptr<Interp4Command> interpCmdPtr = li.createCmd();
    ASSERT_NE(interpCmdPtr, nullptr);
    ASSERT_STREQ(interpCmdPtr->GetCmdName(), "Set");
}

TEST(LibInterfaceTest, createCmdShouldCreateInterp4ComandForRotate) {
    LibInterface li{"Rotate"};
    li.createCmdBuilder();
    std::unique_ptr<Interp4Command> interpCmdPtr = li.createCmd();
    ASSERT_NE(interpCmdPtr, nullptr);
    ASSERT_STREQ(interpCmdPtr->GetCmdName(), "Rotate");
}

TEST(LibInterfaceTest, createCmdShouldCreateInterp4ComandForPause) {
    LibInterface li{"Pause"};
    li.createCmdBuilder();
    std::unique_ptr<Interp4Command> interpCmdPtr = li.createCmd();
    ASSERT_NE(interpCmdPtr, nullptr);
    ASSERT_STREQ(interpCmdPtr->GetCmdName(), "Pause");
}
