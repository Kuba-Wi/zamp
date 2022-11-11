#include "Configuration.hh"

#include <algorithm>

void Configuration::addObject(const std::string& name) {
    if (!this->checkIfObjOpersContainObj(name)) {
        objectsOperations_.emplace_back(name, defaultOperations_.get());
    }
}

void Configuration::addObjOperation(const std::string& objName, 
                       const std::string& operName,
                       const Vector3D& operValues) {

    auto it_pair = std::find_if(objectsOperations_.begin(), 
              objectsOperations_.end(), 
              [&objName](const auto& name_oper_pair){
        return name_oper_pair.first == objName;
    });

    if (it_pair != objectsOperations_.end()) {
        it_pair->second[operName] = operValues;
    }
}

bool Configuration::checkIfObjOpersContainObj(const std::string& objName) {
    return std::any_of(objectsOperations_.begin(), 
              objectsOperations_.end(), 
              [&objName](const auto& name_oper_pair){
        return name_oper_pair.first == objName;
    });
}
