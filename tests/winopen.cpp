// ---   *   ---   *   ---
// deps

  #include "Chasm.hpp"

// ---   *   ---   *   ---
// ROM

  cx64 WINFLAGS=(
    Win::DO_MOUSE_TRAP

  );

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

  auto& win = Chasm.win;
  auto& ev  = Chasm.ev;
  auto& kbd = ev.get_kbd();

  win.set_ambient_color(8);

  while(win.is_open()) {

    ev.poll(&win);

    kbd.run();
    win.refresh(0);

  };

  return 0;

};

// ---   *   ---   *   ---
