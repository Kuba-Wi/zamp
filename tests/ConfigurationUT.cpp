#include <gtest/gtest.h>

#include "Configuration.hh"

TEST(ConfigurationTest, AddLibnameShouldAddLibraryToSet) {
    Configuration config;
    config.addLibName("lib1");
    auto libSet = config.getLibNames();
    ASSERT_EQ(libSet.count("lib1"), 1);
}

TEST(ConfigurationTest, LibraryShouldBeAddedOnceToLibrarySet) {
    Configuration config;
    config.addLibName("lib1");
    config.addLibName("lib1");
    auto libSet = config.getLibNames();
    ASSERT_EQ(libSet.count("lib1"), 1);
}

TEST(ConfigurationTest, addObjectShouldAddObjectToMap) {
    Configuration config;
    config.addObject("Obj1");
    auto objsOperations = config.getObjOperations();
    ASSERT_NE(objsOperations.find("Obj1"), objsOperations.end());
}

TEST(ConfigurationTest, addObjOperationShouldAddObjectOperationToMap) {
    Configuration config;
    Vector3D values;
    values[0] = 0;
    values[1] = 1;
    values[2] = 2;
    config.addObject("Obj1");
    config.addObjOperation("Obj1", "RGB", values);
    auto objsOperations = config.getObjOperations();
    ASSERT_EQ(objsOperations["Obj1"]["RGB"][0], values[0]);
    ASSERT_EQ(objsOperations["Obj1"]["RGB"][1], values[1]);
    ASSERT_EQ(objsOperations["Obj1"]["RGB"][2], values[2]);
}
