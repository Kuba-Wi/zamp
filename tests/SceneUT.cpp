#include <gtest/gtest.h>

#include "Scene.hh"

TEST(SceneTest, AddMobileObjShouldAddMobileObjToScene) {
    Scene scn;
    scn.AddMobileObj("Obj1");
    auto obj_ptr = scn.FindMobileObj("Obj1");
    ASSERT_EQ(obj_ptr->GetName(), "Obj1");
}

TEST(SceneTest, FindMobileObjShouldReturnNullptrWhenNoBojectWasAddedToScene) {
    Scene scn;
    ASSERT_EQ(scn.FindMobileObj("Obj1"), nullptr);
}

TEST(SceneTest, AddObjOperationShouldAddOperationToMobileObject) {
    Scene scn;
    Vector3D values;
    values[0] = 0;
    values[1] = 1;
    values[2] = 2;
    scn.AddMobileObj("Obj1");
    scn.AddObjOperation("Obj1", "RGB", values);
    auto obj_ptr = scn.FindMobileObj("Obj1");
    
    auto name_vec_map = obj_ptr->getVecMap();
    ASSERT_EQ(name_vec_map["RGB"][0], values[0]);
    ASSERT_EQ(name_vec_map["RGB"][1], values[1]);
    ASSERT_EQ(name_vec_map["RGB"][2], values[2]);
}
