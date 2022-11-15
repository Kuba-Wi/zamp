#include "Configuration.hh"

void Configuration::addObject(const std::string& name) {
    objectsOperations_[name] = defaultOperations_.get();
}

void Configuration::addObjOperation(const std::string& objName, 
                       const std::string& operName,
                       const Vector3D& operValues) {

    objectsOperations_[objName][operName] = operValues;
}
