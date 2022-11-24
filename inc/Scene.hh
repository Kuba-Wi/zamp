#pragma once

#include <map>
#include <memory>
#include <string>

#include "MobileObj.hh"

class Scene {
public:
    std::shared_ptr<MobileObj> FindMobileObj(const std::string& rObjName) {
        if (Set_MobileObjs_.find(rObjName) != Set_MobileObjs_.end()) {
            return Set_MobileObjs_[rObjName];
        }
        return nullptr;
    }

    void AddMobileObj(const std::string& name);
    void AddObjOperation(const std::string& objName,
                         const std::string& operName,
                         const Vector3D& values);

    void printObjects();

private:
    std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs_;
};
