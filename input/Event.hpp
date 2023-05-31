#ifndef __5E_EVENT_H__
#define __5E_EVENT_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"

  #include "input/Kbd.hpp"
  #include "input/Rat.hpp"

// ---   *   ---   *   ---
// info

class Event {

public:

  VERSION   "v0.00.3b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// attrs

private:

  Rat m_rat;
  Kbd m_kbd;

// ---   *   ---   *   ---
// guts

  typedef SDL_Event Sev;

  // checks window focus
  bool win_focus(Win* win,Sev* sev);

  // ^controls focus gain/loss
  bool ctl_focus(Win* win,Sev* sev);

  // keep mouse in window if flag set
  void mouse_wrap(Win* win);

  // (possibly redundant)
  // get mouse button as idex
  uint8_t rat_button(uint8_t b);

// ---   *   ---   *   ---
// iface

public:

  int poll(Win* win);

  Kbd& get_kbd(void) {return m_kbd;};
  Rat& get_rat(void) {return m_rat;};

};

// ---   *   ---   *   ---

#endif // __5E_EVENT_H__
