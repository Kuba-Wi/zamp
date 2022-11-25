#include <iostream>
#include <sstream>

#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
    Interp4Command* CreateCmd(void);
    const char* GetCmdName() { return "Set"; }
}

void Interp4Set::ResetParameters() {
    _ObjectName = "";
    _Position_x = 0;
    _Position_y = 0;
    _Angle_Oz = 0;
}

Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

Interp4Set::Interp4Set(): _Position_x(0), _Position_y(0), _Angle_Oz(0)
{}

void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " 
       << _ObjectName << " " 
       << _Position_x << " " 
       << _Position_y << " "
       << _Angle_Oz << endl;
}

const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

bool Interp4Set::ExecCmd(Scene& scn, Communication& com) const
{
  auto obj_ptr = scn.FindMobileObj(_ObjectName);
  if (!obj_ptr) {
    return false;
  }

  obj_ptr->lockAccess();

  auto rot_vec = obj_ptr->getParameterVec("RotXYZ_deg");
  auto trans_tmp = obj_ptr->getParameterVec("Trans_m");
  Vector3D trans_vec;
  trans_vec[0] = _Position_x;
  trans_vec[1] = _Position_y;
  trans_vec[2] = trans_tmp[2];
  rot_vec[2] = _Angle_Oz;

  obj_ptr->SetVectParam("Trans_m", trans_vec);
  obj_ptr->SetVectParam("RotXYZ_deg", rot_vec);

  std::string command;
  std::ostringstream vec_str;

  com.lockAccess();

  command = "UpdateObj Name=";
  command += _ObjectName;
  command += " Trans_m=";
  vec_str << trans_vec;
  command += vec_str.str();
  command += "\n";
  com.Send(command.c_str());

  command = "UpdateObj Name=";
  command += _ObjectName;
  command += " RotXYZ_deg=";
  vec_str = std::ostringstream{};
  vec_str << rot_vec;
  command += vec_str.str();
  command += "\n";
  com.Send(command.c_str());

  obj_ptr->unlockAccess();
  com.unlockAccess();

  return true;
}

bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _ObjectName)) {
    this->ResetParameters();
    return false;
  }
  if (!(Strm_CmdsList >> _Position_x)) {
    this->ResetParameters();
    return false;
  }
  if (!(Strm_CmdsList >> _Position_y)) {
    this->ResetParameters();
    return false;
  }
  if (!(Strm_CmdsList >> _Angle_Oz)) {
    this->ResetParameters();
    return false;
  }

  return true;
}

Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

void Interp4Set::PrintSyntax() const
{
  cout << "   Set  ObjectName  Position_X[m]  Position_Y[m] Angle_OZ[deg]" << endl;
}
