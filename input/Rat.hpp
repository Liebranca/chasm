#ifndef __5E_RAT_H__
#define __5E_RAT_H__

// ---   *   ---   *   ---
// deps

  #include <glm/glm.hpp>

  #include "bitter/kvrnel/Style.hpp"
  #include "Window.hpp"

// ---   *   ---   *   ---
// info

class Rat {
friend class Event;

public:

  VERSION   "v0.00.2b";
  AUTHOR    "IBN-3DILA";

  enum {
    TOP_X=0b0001,
    TOP_Y=0b0010,
    BOT_X=0b0100,
    BOT_Y=0b1000,

  };

  enum {
    LEFT   = 0b00,
    MIDDLE = 0b01,
    RIGHT  = 0b10

  };

// ---   *   ---   *   ---
// helper

  struct Button {
    uint32_t c;
    float    t;

  };

  typedef std::vector<Button> Buttons;

// ---   *   ---   *   ---
// attrs

private:

  glm::uvec2 m_abs;

  glm::vec2  m_rel;
  glm::vec2  m_motion;

  float      m_sens    = 0.65f;
  bool       m_wrapped = false;

  Buttons    m_button  = {

    {0,0},
    {0,0},
    {0,0}

  };

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

  // register button press
  void push(

    uint8_t idex,
    uint8_t clicks,

    bool    rel

  );

// ---   *   ---   *   ---
// iface

public:

  // get movement since last frame
  inline glm::vec2& get_motion(float mult=1.0f) {
    m_motion.x=m_rel.x*mult;
    m_motion.y=m_rel.y*mult;

    return m_motion;

  };

  // get mouse pos was reset this frame
  inline bool wrapped(void) {
    return m_wrapped;

  };

  // get number of clicks for button
  inline uint32_t nclicks(uint8_t idex) {
    return m_button[idex].c;

  };

  // ^get time button is held
  inline float held(
    uint8_t idex,
    float   mult=1.0f

  ) {

    return m_button[idex].t * mult;

  };

  // ^a combination of the two ;>
  inline bool nheld(

    uint8_t idex,
    uint8_t cnt,

    float   len,
    float   mult=1.0f

  ) {

    auto n=this->nclicks(idex);
    auto h=this->held(idex,mult);

    return (n==cnt) && (h > len);

  };

};

// ---   *   ---   *   ---

#endif // __5E_RAT_H__
