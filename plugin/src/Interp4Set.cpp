#include <iostream>

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

bool Interp4Set::ExecCmd(MobileObj *pMobObj, int Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  std::cout << "Executing set: " 
            << _ObjectName << " "
            << _Position_x << " "
            << _Position_y << " "
            << _Angle_Oz << std::endl;

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
