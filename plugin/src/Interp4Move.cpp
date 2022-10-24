#include <iostream>
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

bool Interp4Move::ExecCmd(MobileObj *pMobObj, int Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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
