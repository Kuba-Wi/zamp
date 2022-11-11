#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <map>
#include <set>
#include <string>
#include <vector>

#include "Vector3D.hh"

using oper_map = std::map<std::string, Vector3D>;
using nameOperations_pair = std::pair<std::string, oper_map>;

class defaultOperations {
public:
  defaultOperations() {
    operations_.emplace("Shift", Vector3D{});
    operations_.emplace("Scale", Vector3D{});
    operations_["Scale"][0] = 1;
    operations_["Scale"][1] = 1;
    operations_["Scale"][2] = 1;

    operations_.emplace("RotXYZ_deg", Vector3D{});
    operations_.emplace("Trans_m", Vector3D{});
    operations_.emplace("RGB", Vector3D{});
    operations_["RGB"][0] = 128;
    operations_["RGB"][1] = 128;
    operations_["RGB"][2] = 128;
  }

  const oper_map& get() const { return operations_; }
private:
  oper_map operations_;
};


class Configuration {
public:
  void addLibName(const std::string& libname) { libNames_.emplace(libname); }
  void addObject(const std::string& name);
  void addObjOperation(const std::string& objName, 
                       const std::string& operName,
                       const Vector3D& operValues);

  const std::set<std::string>& getLibNames() const { return libNames_; }
  const std::vector<nameOperations_pair>& getObjOperations() const { return objectsOperations_; }

// private:
  bool checkIfObjOpersContainObj(const std::string& objName);

  std::set<std::string> libNames_;
  std::vector<nameOperations_pair> objectsOperations_;
  const defaultOperations defaultOperations_;
};

#endif
