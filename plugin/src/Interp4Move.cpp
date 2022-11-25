#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>

#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
  Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}

void Interp4Move::ResetParameters() {
  _ObjectName = "";
  _Speed_mS = 0;
  _Distance_m = 0;
}

Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}

Interp4Move::Interp4Move(): _Speed_mS(0), _Distance_m(0)
{}

void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << " " << _ObjectName << " " << _Speed_mS  << " " << _Distance_m << endl;
}

const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}

bool Interp4Move::ExecCmd(Scene& scn, Communication& com) const
{
  auto obj_ptr = scn.FindMobileObj(_ObjectName);
  if (!obj_ptr) {
    return false;
  }

  const double pi = std::acos(-1);
  double alpha, beta, gamma;
  const size_t fraction = 100;
  double sleep_time = _Distance_m / _Speed_mS / fraction;
  std::string command;
  std::ostringstream vec_str;
  Vector3D move_vector, rot_vec, trans_vec;

  for (size_t i = 0; i < fraction; ++i) {
    obj_ptr->lockAccess();
    rot_vec = obj_ptr->getParameterVec("RotXYZ_deg");
    trans_vec = obj_ptr->getParameterVec("Trans_m");

    alpha = rot_vec[0] * pi / 180;
    beta = rot_vec[1] * pi / 180;
    gamma = rot_vec[2] * pi / 180;
    move_vector[0] = (cos(alpha)*sin(beta)*cos(gamma) + sin(alpha)*sin(gamma)) * _Distance_m;
    move_vector[1] = (cos(alpha)*sin(beta)*sin(gamma) - sin(alpha)*cos(gamma)) * _Distance_m;
    move_vector[2] = cos(alpha)*cos(beta) * _Distance_m;

    for (size_t j = 0; j < 3; ++j) {
      trans_vec[j] += (move_vector[j] / fraction);
    }
    obj_ptr->SetVectParam("Trans_m", trans_vec);

    command = "UpdateObj Name=";
    command += _ObjectName;
    command += " Trans_m=";

    vec_str = std::ostringstream{};
    vec_str << trans_vec;
    command += vec_str.str();
    command += "\n";
    com.Send(command.c_str());
    obj_ptr->unlockAccess();

    std::this_thread::sleep_for(std::chrono::milliseconds(int(sleep_time * 1000)));
  }

  return true;
}

bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _ObjectName)) {
    this->ResetParameters();
    return false;
  }
  if (!(Strm_CmdsList >> _Speed_mS)) {
    this->ResetParameters();
    return false;
  }
  if (!(Strm_CmdsList >> _Distance_m)) {
    this->ResetParameters();
    return false;
  }

  return true;
}

Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

void Interp4Move::PrintSyntax() const
{
  cout << "   Move  ObjectName  Speed[m/s]  Distance[m]" << endl;
}
