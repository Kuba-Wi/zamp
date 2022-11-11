#pragma once

#include <map>
#include <memory>
#include <string>

#include "MobileObj.hh"

class Scene {
public:
    std::shared_ptr<MobileObj> FindMobileObj(const char* sObjName);
    std::shared_ptr<MobileObj> FindMobileObj(const std::string& rObjName);
    void AddMobileObj(const std::string& name);
    void AddObjOperation(const std::string& objName,
                         const std::string& operName,
                         const Vector3D& values);

    void printObjects();

private:
    std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs_;
};
