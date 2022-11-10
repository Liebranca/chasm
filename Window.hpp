#ifndef __5E_WINDOW_H__
#define __5E_WINDOW_H__

// ---   *   ---   *   ---
// deps

  #include <SDL2/SDL.h>

  #include "bitter/kvrnel/Style.hpp"
  #include "bitter/kvrnel/Clock.hpp"

// ---   *   ---   *   ---
// info

class Win {

public:

  VERSION   "v1.00.2";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// flags listing

  enum winflags {
    isOpen,
    numFlags

  };

// ---   *   ---   *   ---
// helpers

  typedef struct {

    std::string title;

    int         width;
    int         height;

    bool        fullscreen;
    float       fps;

  } Desc;

  static Desc DEFDESC;

// ---   *   ---   *   ---
// attrs

private:

  SDL_Window*   m_handle;
  SDL_GLContext m_gl_ctx;

  uint64_t      m_flags;
  Clock         m_clk;

// ---   *   ---   *   ---
// legacy: 16-color palette

  uint32_t m_pal_u[0x10]={

    0x000000FF,0x7F0000FF,
    0x208020FF,0xD09820FF,
    0x0060B0FF,0x400040FF,
    0x008080FF,0xB8B8B8FF,

    0x000080FF,0xA01020FF,
    0x40AE40FF,0xB0B000FF,
    0x0040B0FF,0x8000A0FF,
    0x00A0A0FF,0xB0A060FF

  };

  float   m_pal[0x40] = {0};

  float   m_amx       = 1.0f;
  uint8_t m_amc       = 0;

// ---   *   ---   *   ---
// guts

  inline void set_flag(uint8_t x) {
    m_flags|=0x1LL<<x;

  };

  inline void unset_flag(uint8_t x) {
    m_flags&=~ (0x1LL<<x);

  };

  int sdl_nit(void);
  int spawn(Win::Desc& desc);
  int gl_nit(void);

// ---   *   ---   *   ---
// iface

public:

  // creates window
  Win(Win::Desc& desc=Win::DEFDESC);

  // destroys window
  ~Win(void);

  // loop top
  void refresh(int busy);

  // setters
  void set_palette(uint32_t* src);

  inline void set_ambient_color(
    uint8_t idex

  ) {m_amc=idex;};

  inline void set_ambient_mult(
    float x

  ) {m_amx=x;};

};

// ---   *   ---   *   ---

#endif // __5E_WINDOW_H__

