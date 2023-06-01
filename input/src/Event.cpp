// ---   *   ---   *   ---
// EVENT
// Picks up inputs
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include <cstdio>
  #include "input/Event.hpp"

// ---   *   ---   *   ---
// entry point
// handler forks off from here

int Event::poll(Win* win) {

  int rat_state = 0b001;
  int out       = 0;

  Sev sev;

  this->mouse_wrap(win);

  while(SDL_PollEvent(&sev)) {

    if(! win_focus(win,&sev)) {
      continue;

    };

    bool     rat_rel   = false;
    uint8_t  rat_key   = 0;

    bool     kbd_rel   = false;
    uint32_t kbd_key   = 0;

    switch(sev.type) {

// ---   *   ---   *   ---
// keyboard

    case SDL_KEYUP:
      kbd_rel=true;

    case SDL_KEYDOWN:
      kbd_key=sev.key.keysym.scancode;

      m_kbd.push(kbd_key,kbd_rel);
      out|=1;

      break;

// ---   *   ---   *   ---
// mouse

    case SDL_MOUSEMOTION:

      m_rat.run(&sev.motion);

      rat_state &=~ 0b001;
      out       |=  1;

      break;

    case SDL_MOUSEBUTTONUP:
      rat_rel=true;

    case SDL_MOUSEBUTTONDOWN:
      rat_key=rat_button(sev.button.button);
      m_rat.push(rat_key,sev.button.clicks,rat_rel);

      out|=1;
      break;

// ---   *   ---   *   ---
// TODO: joystick

// ---   *   ---   *   ---

    };

  };

  if(rat_state&1) {
    m_rat.reset_motion();

  };

  return out;

};

// ---   *   ---   *   ---
// checks window focus

bool Event::win_focus(Win* win,Sev* sev) {

  bool     out     = false;

  uint32_t focused = sev->window.windowID;
  uint32_t passed  = SDL_GetWindowID(win->handle());

  // polled window is active
  if(focused==passed) {

    // check for state change
    // else return last state
    out=(sev->type == SDL_WINDOWEVENT)
      ? this->ctl_focus(win,sev)
      : win->focused()
      ;

  };

  return out;

};

// ---   *   ---   *   ---
// ^control focus gain/loss

bool Event::ctl_focus(Win* win,Sev* sev) {

  win->update_wflags();

  bool mouse_trap=win->mouse_trap();
  bool mouse_hide=false;

  switch(sev->window.event) {

  // on enter
  case SDL_WINDOWEVENT_FOCUS_GAINED:

    mouse_hide=
      SDL_DISABLE
    | (! mouse_trap)
    ;

    SDL_ShowCursor(mouse_hide);
    win->set_flag(Win::IS_FOCUS);

    break;

  // on leave
  case SDL_WINDOWEVENT_FOCUS_LOST:

    mouse_hide=
      SDL_ENABLE
    | mouse_trap
    ;

    SDL_ShowCursor(mouse_hide);
    win->unset_flag(Win::IS_FOCUS);

    break;

  };

  return win->focused();

};

// ---   *   ---   *   ---
// keep mouse in window if flag set

void Event::mouse_wrap(Win* win) {

  bool do_wrap=(win->is_fullscreen())
    ? win->fullscreen_do_wrap()
    : win->windowed_do_wrap()
    ;

  if(do_wrap) {
    m_rat.reset(win);

  };

};

// ---   *   ---   *   ---
// (possibly redundant)
// get mouse button as idex

uint8_t Event::rat_button(uint8_t b) {

  return

    (Rat::LEFT)

  | (Rat::MIDDLE * (b==SDL_BUTTON_MIDDLE))
  | (Rat::RIGHT  * (b==SDL_BUTTON_RIGHT))

  ;

};

// ---   *   ---   *   ---
