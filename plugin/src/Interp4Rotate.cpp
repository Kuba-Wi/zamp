#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
    Interp4Command* CreateCmd(void);
    const char* GetCmdName() { return "Rotate"; }
}

void Interp4Rotate::ResetParameters() {
    _ObjectName = "";
    _Speed = 0;
    _Angle = 0;
}

Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}

Interp4Rotate::Interp4Rotate(): _Speed(0), _Angle(0)
{}

void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " " << _ObjectName << " " << _Speed << " " << _Angle << " " << endl;
}

const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}

bool Interp4Rotate::ExecCmd(Scene& scn, Communication& com) const
{
  auto obj_ptr = scn.FindMobileObj(_ObjectName);
  if (!obj_ptr) {
    return false;
  }

  const size_t fraction = 100;
  double sleep_time = _Angle / _Speed / fraction;
  std::string command;
  std::ostringstream vec_str;
  Vector3D rot_vec, rot_tmp;
  double alpha, beta, gamma;
  const double pi = std::acos(-1);

  for (size_t i = 0; i < fraction; ++i) {
    obj_ptr->lockAccess();
    rot_vec = obj_ptr->getParameterVec("RotXYZ_deg");
    alpha = rot_vec[0] * pi / 180;
    beta = rot_vec[1] * pi / 180;
    gamma = rot_vec[2] * pi / 180;
    rot_tmp[0] = (cos(alpha)*sin(beta)*cos(gamma) + sin(alpha)*sin(gamma)) * _Angle;
    rot_tmp[1] = (cos(alpha)*sin(beta)*sin(gamma) - sin(alpha)*cos(gamma)) * _Angle;
    rot_tmp[2] = cos(alpha)*cos(beta) * _Angle;

    for (size_t j = 0; j < 3; ++j) {
      rot_vec[j] += (rot_tmp[j] / fraction);
    }

    obj_ptr->SetVectParam("RotXYZ_deg", rot_vec);

    command = "UpdateObj Name=";
    command += _ObjectName;
    command += " RotXYZ_deg=";

    vec_str = std::ostringstream{};
    vec_str << rot_vec;
    command += vec_str.str();
    command += "\n";
    com.Send(command.c_str());
    obj_ptr->unlockAccess();
    std::this_thread::sleep_for(std::chrono::milliseconds(int(sleep_time * 1000)));
  }

  return true;
}

bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _ObjectName)) {
    this->ResetParameters();
    return false;
  }
  if (!(Strm_CmdsList >> _Speed)) {
    this->ResetParameters();
    return false;
  }
  if (!(Strm_CmdsList >> _Angle)) {
    this->ResetParameters();
    return false;
  }

  return true;
}

Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}

void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate ObjectName Speed[deg/s] Angle[deg]" << endl;
}
