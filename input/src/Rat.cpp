// ---   *   ---   *   ---
// RAT
// Also known as Mickey
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include "input/Rat.hpp"

// ---   *   ---   *   ---
// center mouse on win

void Rat::reset(Win* win) {

  m_abs   = win->hsize();

  m_rel.x = 0.0f;
  m_rel.y = 0.0f;

  SDL_WarpMouseInWindow(
    win->handle(),m_abs.x,m_abs.y

  );

  m_wrapped=true;

};

// ---   *   ---   *   ---
// get bmask for which corners
// of win rat touches

uint8_t Rat::at_wall(Win* win) {

  auto&   size = win->size();

  uint8_t out  = (

  // upper edge
    ((m_abs.x == 0        ) << 0)
  | ((m_abs.y == 0        ) << 1)

  // lower edge
  | ((m_abs.x == size.x-1) << 2)
  | ((m_abs.y == size.y-1) << 3)

  );

  return out;

};

// ---   *   ---   *   ---
// make note of movements

void Rat::run(Motion* motion) {

  this->reset_motion();

  // set position
  m_abs.x  = motion->x;
  m_abs.y  = motion->y;

  // cancel motion if
  // caused by mouse trap
  m_rel.x  = (float) (

      motion->xrel

  *   m_sens
  * ! m_wrapped

  );

  m_rel.y  = (float) (

    motion->yrel

  *   m_sens
  * ! m_wrapped

  );

  m_wrapped = false;

};

// ---   *   ---   *   ---
// ^clears at frame end

void Rat::reset_motion(void) {
  m_motion.x=0.0f;
  m_motion.y=0.0f;

};

// ---   *   ---   *   ---
// updates timer on held buttons

void Rat::update_buttons(void) {

  for(uint8_t i=0;i<NUM_BUTTONS;i++) {

    auto& b = m_button[i];

    // or tap, doesnt matter at this stage
    bool  held = b.c != 0;

    // two-frame check:
    // just released v released a frame ago
    bool  released = b.t == -1.0f;
    bool  inactive = b.t == -2.0f;

    b.t += 1.0f * held;
    b.t -= 1.0f * released;

    // ^conditional sum
    b.t  =
      (b.t * held)
    + (b.t * released)
    ;

  };

};

// ---   *   ---   *   ---
// register button press

void Rat::push(

  uint8_t idex,
  uint8_t clicks,

  bool    rel

) {

  m_button[idex].c=(
    m_button[idex].c
  + clicks
  ) *! rel;

  // negative time signals release
  m_button[idex].t=
    (m_button[idex].t  *! rel)
  - (1.0f *  rel)
  ;

};

// ---   *   ---   *   ---
