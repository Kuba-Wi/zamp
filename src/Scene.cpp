#include "Scene.hh"

#include <iostream>

std::shared_ptr<MobileObj> Scene::FindMobileObj(const char* sObjName) {
    return this->FindMobileObj(std::string{sObjName});
}

std::shared_ptr<MobileObj> Scene::FindMobileObj(const std::string& rObjName) {
    if (Set_MobileObjs_.find(rObjName) != Set_MobileObjs_.end()) {
        return Set_MobileObjs_[rObjName];
    }
    return nullptr;
}

void Scene::AddMobileObj(const std::string& name) {
    Set_MobileObjs_[name] = std::make_shared<MobileObj>();
    Set_MobileObjs_[name]->SetName(name.c_str());
}

void Scene::AddObjOperation(const std::string& objName,
                         const std::string& operName,
                         const Vector3D& values) {

    Set_MobileObjs_[objName]->SetVectParam(operName, values);
}

void Scene::printObjects() {
    for (const auto& [_, obj] : Set_MobileObjs_) {
        std::cout << obj->GetName() << ":\n";
        for (const auto& [name, val] : obj->getVecMap()) {
            std::cout << "\t" << name << " " << val << "\n";
        }
    }
}
