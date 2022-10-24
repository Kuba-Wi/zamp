#include <iostream>

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

bool Interp4Rotate::ExecCmd(MobileObj *pMobObj, int Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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
