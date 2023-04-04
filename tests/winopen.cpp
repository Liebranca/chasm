// ---   *   ---   *   ---
// deps

  #include "Chasm.hpp"

// ---   *   ---   *   ---
// ROM

  cx64 WINFLAGS=(
    Win::DO_MOUSE_TRAP

  );

// ---   *   ---   *   ---
// test logic

int ltest(void* data) {
  return 0;

};

int dtest(void* data) {
  static int color=0;
  Chasm.win.set_ambient_color(color);

  color++;
  color&=0xF;

  return 0;

};

// ---   *   ---   *   ---

int main(void) {

  Win::Desc desc={

    .title      = "hello-chasm",

    .width      = 640,
    .height     = 480,

    .fullscreen = 0,
    .fps        = 6,

    .flags      = WINFLAGS

  };

  Chasm.nit(desc);

  Chasm.draw  = &dtest;
  Chasm.logic = &ltest;

  CHASM_RUN(NULL,NULL);

  return 0;

};

// ---   *   ---   *   ---
