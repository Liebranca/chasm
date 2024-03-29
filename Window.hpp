#ifndef __5E_WINDOW_H__
#define __5E_WINDOW_H__

// ---   *   ---   *   ---
// deps

  #include <glm/glm.hpp>
  #include <SDL2/SDL.h>

  #include "bitter/kvrnel/Style.hpp"
  #include "bitter/kvrnel/Evil.hpp"
  #include "bitter/kvrnel/Clock.hpp"

// ---   *   ---   *   ---
// info

class Win {
friend class Event;

public:

  VERSION   "v1.00.8";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// errmes

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

  SDL_Window*   m_handle=NULL;
  SDL_GLContext m_gl_ctx;

  uint64_t      m_flags;
  Clock         m_clk;

  glm::uvec2    m_size;
  glm::uvec2    m_hsize;

  // sdl window flags,
  // distinct from m_flags!
  uint32_t      m_wflags;

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

  inline void set_flag(uint64_t x) {
    m_flags |=  x;

  };

  inline void unset_flag(uint64_t x) {
    m_flags &=~ x;

  };

  void sdl_nit(void);
  void spawn(Win::Desc& desc);
  void gl_nit(void);

  void calc_size(void);

  void update_wflags(void) {
    m_wflags=SDL_GetWindowFlags(m_handle);

  };

// ---   *   ---   *   ---
// iface

public:

  // ctrash
  Win(void) {};

  // creates window
  void nit(Win::Desc& desc);

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

  inline Clock& clock(void) {
    return m_clk;

  };

  inline bool focused(void) {
    return m_flags & Win::IS_FOCUS;

  };

  inline bool mouse_trap(void) {
    return m_flags & Win::DO_MOUSE_TRAP;

  };

  // lock/unlock cursor
  void disable_mouse_trap(void);
  void enable_mouse_trap(void);

  inline glm::uvec2& size(void) {
    return m_size;

  };

  inline glm::uvec2& hsize(void) {
    return m_hsize;

  };

  uint32_t wflags(void) {
    return m_wflags;

  };

  bool is_fullscreen(void) {
    return
      m_wflags
    & SDL_WINDOW_FULLSCREEN_DESKTOP
    ;

  };

  bool is_minimized(void) {
    return
      m_wflags
    & SDL_WINDOW_MINIMIZED
    ;

  };

  // wrap mouse if window is NOT fullscreen
  bool windowed_do_wrap(void) {
    return
       this->mouse_trap()
    && this->focused()
    ;

  };

  // ^window IS fullscreen
  bool fullscreen_do_wrap(void) {
    return ! this->is_minimized();

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

