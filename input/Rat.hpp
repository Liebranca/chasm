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

  VERSION   "v0.00.6b";
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

  // mouse-motion epsilon
  cxr32 MOEPS=0.001f;

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
  float      m_wheel   = 0.00f;

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

  // registers wheel scroll
  void set_wheel(int32_t y) {
    m_wheel=(float) y;

  };

// ---   *   ---   *   ---
// iface

public:

  // get movement since last frame
  inline glm::vec2& get_motion(float mult=1.0f) {

    m_motion.x  = m_rel.x * mult;
    m_motion.y  = m_rel.y * mult;

    float eps   = MOEPS / mult;

    // clamp if below epsilon
    m_motion.x *= fabs(m_motion.x) > eps;
    m_motion.y *= fabs(m_motion.y) > eps;

    return m_motion;

  };

  // ^clears at frame end
  void reset_motion(void);
  void reset_button(void);

  // get scrolling
  inline float wheel(void) {
    return m_wheel;

  };

  // get absolute position in screen cords
  inline glm::uvec2& get_position(void) {
    return m_abs;

  };

  // get mouse pos was reset this frame
  inline bool wrapped(void) {
    return m_wrapped;

  };

  // get number of clicks for button
  inline uint32_t clicks(uint8_t idex) {
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
  inline bool clicks_held(

    uint8_t idex,
    uint8_t cnt,

    float   len,
    float   mult=1.0f

  ) {

    auto c=this->clicks(idex);
    auto h=this->held(idex,mult);

    return (c==cnt) && (h > len);

  };

};

// ---   *   ---   *   ---

#endif // __5E_RAT_H__
