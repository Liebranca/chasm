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

  #include "Rat.hpp"
  #include "Event.hpp"

// ---   *   ---   *   ---
// entry point
// handler forks off from here

int Event::poll(Win* win) {

  int out=0;
  Sev sev;


  this->mouse_wrap(win);

  while(SDL_PollEvent(&sev)) {

    if(! win_focus(win,&sev)) {
      continue;

    };

    out|=1;
    switch(sev.type) {

// ---   *   ---   *   ---
// keyboard

    case SDL_KEYUP:

      if(sev.key.keysym.sym==SDLK_ESCAPE) {
        win->close();

      };

      m_kbd.push(sev.key.keysym.scancode,true);
      break;

    case SDL_KEYDOWN:
      m_kbd.push(sev.key.keysym.scancode,false);
      break;

// ---   *   ---   *   ---
// mouse

    case SDL_MOUSEMOTION:
      break;

    case SDL_MOUSEBUTTONUP:
      break;

    case SDL_MOUSEBUTTONDOWN:
      break;

// ---   *   ---   *   ---
// TODO: joystick

// ---   *   ---   *   ---

    };

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

  uint32_t wflags =
    SDL_GetWindowFlags(win->handle());

  bool mouse_trap = win->mouse_trap();
  bool focused    = win->focused();

  bool fullscreen =
    wflags & SDL_WINDOW_FULLSCREEN_DESKTOP;

  bool minimized  =
    wflags & SDL_WINDOW_MINIMIZED;

  bool do_wrap    = (fullscreen)
    ? m_rat.at_wall(win)
    : focused
    ;

  do_wrap*=mouse_trap*(! minimized);

  if(do_wrap) {
    m_rat.reset(win);

  };

};

// ---   *   ---   *   ---