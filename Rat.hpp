#ifndef __5E_RAT_H__
#define __5E_RAT_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"
  #include "Window.hpp"

// ---   *   ---   *   ---
// info

class Rat {
friend class Event;

public:

  VERSION   "v0.00.1b";
  AUTHOR    "IBN-3DILA";

  enum {
    TOP_X=0b0001,
    TOP_Y=0b0010,
    BOT_X=0b0100,
    BOT_Y=0b1000,

  };

// ---   *   ---   *   ---
// attrs

private:

  uint32_t m_abs[2];
  float    m_rel[2];
  float    m_motion[2];

  float    m_sens    = 0.65f;
  bool     m_wrapped = false;

  typedef SDL_MouseMotionEvent Motion;

// ---   *   ---   *   ---
// guts

  // center mouse on win
  void reset(Win* win);

  // get bmask for which corners
  // of win rat touches
  uint8_t at_wall(Win* win);

  // make note of movements
  void run(Motion* motion);

// ---   *   ---   *   ---
// iface

public:

  // get movement since last frame
  inline float* get_motion(float mult=1.0f) {
    m_motion[0]=m_rel[0]*mult;
    m_motion[1]=m_rel[1]*mult;

    return &m_motion[0];

  };

  // get mouse pos was reset this frame
  inline bool wrapped(void) {
    return m_wrapped;

  };

};

// ---   *   ---   *   ---

#endif // __5E_RAT_H__
