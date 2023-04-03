// ---   *   ---   *   ---
// deps

  #include "Window.hpp"
  #include "Event.hpp"

  #include "Kbdlay.hpp"

// ---   *   ---   *   ---
// ROM

  cx64 WINFLAGS=(
    Win::DO_MOUSE_TRAP

  );

// ---   *   ---   *   ---

static void ktest(Kbd::Key& key) {
  printf("!",key.state);

};

BEG_KEYSET(ks)

  {left,{
    &ktest,
    &ktest,
    &ktest

  }}

END_KEYSET;

// ---   *   ---   *   ---

int main(void) {

  Win::Desc wind={

    .title      = "hello-chasm",

    .width      = 640,
    .height     = 480,

    .fullscreen = 0,
    .fps        = 6,

    .flags      = WINFLAGS

  };

  Win   win(wind);
  Event ev;

  Kbd&  kbd=ev.get_kbd();

  kbd.set_remap(Keysets::ks);
  win.set_ambient_color(8);

  auto& key=kbd.key(Keysets::ks[0].id);

  while(win.is_open()) {
    ev.poll(&win);

    printf("%03B ",key.state);

    kbd.run();

    printf("\n");

    win.refresh(0);

  };

  return 0;

};

// ---   *   ---   *   ---
