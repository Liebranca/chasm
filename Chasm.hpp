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

  // placeholder for main
  typedef int(*Loop) (void* data);
  static int empty_loop(void* data) {return 0;};

  // attrs
  Win   win;
  Event ev;

  Loop  draw  = &empty_loop;
  Loop  logic = &empty_loop;

  // ctrash
  CHASM(void) {};
  ~CHASM(void) {};

  // cstruc
  void nit(
    Win::Desc&   desc=Win::DEFDESC,
    Kbd::Keyset& keys=Kbd::DEFKEYS

  );

  // main skeleton
  void run(
    void* draw_data  = NULL,
    void* logic_data = NULL

  );

};

// ---   *   ---   *   ---
// singleton

extern CHASM Chasm;

// ^default die
static void chasm_exit(void) {
  Chasm.win.close();

};

#define CHASM_RUN(x,y) \
  while(Chasm.win.is_open()) { \
    Chasm.run((x),(y)); \
  }

// ---   *   ---   *   ---

#endif // __5E_CHASM_H__
