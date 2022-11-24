#ifndef  COMMAND4MOVE_HH
#define  COMMAND4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

#include <string>

/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicję klasy Interp4Move ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Move: public Interp4Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */
  std::string _ObjectName;
  double _Speed_mS;
  double _Distance_m;

  void ResetParameters();

 public:
  /*!
   * \brief
   */
  Interp4Move();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  void PrintCmd() const override;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  void PrintSyntax() const override;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  const char* GetCmdName() const override;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  bool ExecCmd(Scene& scn, Communication& com) const override;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  bool ReadParams(std::istream& Strm_CmdsList) override;
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
