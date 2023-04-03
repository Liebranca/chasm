// ---   *   ---   *   ---
// deps

  #include "Window.hpp"
  #include "Event.hpp"

// ---   *   ---   *   ---
// ROM

  cx64 WINFLAGS=(
    Win::DO_MOUSE_TRAP

  );

// ---   *   ---   *   ---

static void ktest(Kbd::Key& key) {
  printf("!",key.state);

};

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

  Kbd::Cback cbacks[3]={
    &ktest,&ktest,&ktest

  };

  kbd.remap(0x35,&cbacks[0]);
  win.set_ambient_color(8);

  auto& key=kbd.key(0x35);

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
