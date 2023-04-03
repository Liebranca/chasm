#ifndef __5E_WINDOW_H__
#define __5E_WINDOW_H__

// ---   *   ---   *   ---
// deps

  #include <SDL2/SDL.h>

  #include "bitter/kvrnel/Style.hpp"
  #include "bitter/kvrnel/Evil.hpp"
  #include "bitter/kvrnel/Clock.hpp"

// ---   *   ---   *   ---
// info

class Win {
friend class Event;

public:

  VERSION   "v1.00.5";
  AUTHOR    "IBN-3DILA";

  struct Error {

    CX Evil::Errcode SDL_NIT {

      .type=AR_FATAL,

      .code=__COUNTER__,
      .mess="SDL init failed"

    };

    CX Evil::Errcode GL_CTX {

      .type=AR_FATAL,

      .code=__COUNTER__,
      .mess="Could not create GL context"

    };

    CX Evil::Errcode GLEW_NIT {

      .type=AR_FATAL,

      .code=__COUNTER__,
      .mess="GLEW init failed"

    };

    CX Evil::Errcode WIN_OPEN {

      .type=AR_FATAL,

      .code=__COUNTER__,
      .mess="Could not open new window"

    };

  };

// ---   *   ---   *   ---
// flags listing

  enum winflags {

    IS_OPEN  = 0x01,
    IS_FOCUS = 0x02,

    DO_MOUSE_TRAP = 0x0100

  };

// ---   *   ---   *   ---
// helpers

  typedef struct {

    std::string title;

    int         width;
    int         height;

    bool        fullscreen;
    float       fps;

    uint64_t    flags;

  } Desc;

  static Desc DEFDESC;

// ---   *   ---   *   ---
// attrs

private:

  SDL_Window*   m_handle;
  SDL_GLContext m_gl_ctx;

  uint64_t      m_flags;
  Clock         m_clk;

  uint32_t      m_size[2];
  uint32_t      m_hsize[2];

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
    m_flags |=  x;

  };

  inline void unset_flag(uint8_t x) {
    m_flags &=~ x;

  };

  void sdl_nit(void);
  void spawn(Win::Desc& desc);
  void gl_nit(void);

  void calc_size(void);

// ---   *   ---   *   ---
// iface

public:

  // creates window
  Win(Win::Desc& desc=Win::DEFDESC);

  // destroys window
  ~Win(void);

  // loop top
  void refresh(int busy);

  // loop condition
  inline bool is_open(void) {
    return m_flags & Win::IS_OPEN;

  };

  // ^unlock
  inline void close(void) {
    this->unset_flag(Win::IS_OPEN);

  };

  // getters
  inline SDL_Window* handle(void) {
    return m_handle;

  };

  inline bool focused(void) {
    return m_flags & Win::IS_FOCUS;

  };

  inline bool mouse_trap(void) {
    return m_flags & Win::DO_MOUSE_TRAP;

  };

  inline uint32_t* size(void) {
    return &m_size[0];

  };

  inline uint32_t* hsize(void) {
    return &m_hsize[0];

  };

  // setters
  void set_palette(uint32_t* src);

  inline void set_ambient_color(
    uint8_t idex

  ) {m_amc=idex*4;};

  inline void set_ambient_mult(
    float x

  ) {m_amx=x;};

};

// ---   *   ---   *   ---

#endif // __5E_WINDOW_H__

