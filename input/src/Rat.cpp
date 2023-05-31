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

  m_abs.x  = motion->x;
  m_abs.y  = motion->y;

  m_rel.x  = (float) (motion->xrel * m_sens);
  m_rel.y  = (float) (motion->yrel * m_sens);

  m_wrapped = false;

  m_button[LEFT].t+=
    1.0f * (m_button[LEFT].t > 0);

  m_button[MIDDLE].t+=
    1.0f * (m_button[MIDDLE].t > 0);

  m_button[RIGHT].t+=
    1.0f * (m_button[RIGHT].t > 0);

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
  ) * ! rel;

  m_button[idex].t=(
    m_button[idex].t
  + 1.0f

  ) * ! rel;

};

// ---   *   ---   *   ---
