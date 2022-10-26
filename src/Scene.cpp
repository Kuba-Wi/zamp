#include "Scene.hh"

std::shared_ptr<MobileObj> Scene::FindMobileObj(const char* sObjName) {
    return this->FindMobileObj(std::string{sObjName});
}

std::shared_ptr<MobileObj> Scene::FindMobileObj(const std::string& rObjName) {
    if (Set_MobileObjs_.find(rObjName) != Set_MobileObjs_.end()) {
        return nullptr;
    }
    return Set_MobileObjs_[rObjName];
}
