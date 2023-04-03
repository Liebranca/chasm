#ifndef __5E_CHASM_H__
#define __5E_CHASM_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"
  #include "Event.hpp"

// ---   *   ---   *   ---
// info

class CHASM {

public:

  VERSION   "v2.04.0";
  AUTHOR    "IBN-3DILA";

  // attrs
  Win   win;
  Event ev;

  // ctrash
  CHASM(void) {};
  ~CHASM(void) {};

  // cstruc
  void nit(
    Win::Desc&   desc=Win::DEFDESC,
    Kbd::Keyset& keys=Kbd::DEFKEYS

  );

};

// ---   *   ---   *   ---
// singleton

extern CHASM Chasm;

// ^default die
static void chasm_exit(void) {
  Chasm.win.close();

};

// ---   *   ---   *   ---

#endif // __5E_CHASM_H__
