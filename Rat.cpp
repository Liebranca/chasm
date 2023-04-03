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

  #include "Rat.hpp"

// ---   *   ---   *   ---
// center mouse on win

void Rat::reset(Win* win) {

  uint32_t* hsize=win->hsize();

  m_abs[0]=hsize[0];
  m_abs[1]=hsize[1];

  m_rel[0]=0.0f;
  m_rel[1]=0.0f;

  SDL_WarpMouseInWindow(
    win->handle(),m_abs[0],m_abs[1]

  );

  m_wrapped=true;

};

// ---   *   ---   *   ---
// get bmask for which corners
// of win rat touches

uint8_t Rat::at_wall(Win* win) {

  uint32_t* size = win->size();

  uint8_t   out  = (

  // upper edge
    ((m_abs[0] == 0        ) << 0)
  | ((m_abs[1] == 0        ) << 1)

  // lower edge
  | ((m_abs[0] == size[0]-1) << 2)
  | ((m_abs[1] == size[1]-1) << 3)

  );

  return out;

};

// ---   *   ---   *   ---
// make note of movements

void Rat::run(Motion* motion) {

  m_abs[0]  = motion->x;
  m_abs[1]  = motion->y;

  m_rel[0]  = (float) (motion->xrel * m_sens);
  m_rel[1]  = (float) (motion->yrel * m_sens);

  m_wrapped = false;

};

// ---   *   ---   *   ---
