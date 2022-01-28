// ---   *   ---   *   ---
// WINDOW
// Just a canvas
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,
// ---   *   ---   *   ---

// deps

  #include "window.h"

  #include <stdlib.h>
  #include <stdio.h>

  #include <GL/glew.h>
  #include <SDL2/SDL.h>

  #include "ce/clock.h"

// ---   *   ---   *   ---
// global state

typedef struct {

  SDL_Window* h;
  SDL_GLContext gl_ctx;

  long flags;

} WIN;static WIN win={0};

// ---   *   ---   *   ---
// graphics refs

  float** palette;
  float* ambient;

void wingrefs(
  float** pal,
  float* am

) {palette=pal;ambient=am;};

// ---   *   ---   *   ---
// flags listing

enum winflags {
  win_isOpen,
  win_numFlags

};

// set/unset shorthand macros
#define FSET(flag) win.flags|=((0x1LL)<<flag)
#define FUST(flag) win.flags&=~((0x1LL)<<flag)

// errhandling shorthand
#define ERR(label,me) errme=me;goto label

// ---   *   ---   *   ---

// spawns a window
int winnt(
  const char* title,

  int width,
  int height,

  int fullscreen

) {

  // dummy for error messages
  char* errme=NULL;


  // set gl attributes
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE,4);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,4);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,4);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,4);

  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,16);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);

  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_PROFILE_MASK,
    SDL_GL_CONTEXT_PROFILE_CORE

  );

  // nit and catch
  if(SDL_Init(SDL_INIT_VIDEO)<0) {
    ERR(ABORT,"SDL init failed");

  };

// ---   *   ---   *   ---

  // spawn the window
  if(!(win.h=SDL_CreateWindow(

    title,

    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,

    width,
    height,

    SDL_WINDOW_OPENGL|SDL_WINDOW_BORDERLESS
   |(SDL_WINDOW_FULLSCREEN_DESKTOP*fullscreen)

// ---   *   ---   *   ---

  // catch
  ))) {

    ERR(ABORT,"Could not create window");

  };FSET(win_isOpen);

  // make gl context
  if(!(win.gl_ctx=SDL_GL_CreateContext(win.h))) {
    ERR(ABORT,"Could not create GL context");

  };

  // nit glew
  if(glewInit()) {
    ERR(ABORT,"GLEW init failed");

  };SDL_GL_SetSwapInterval(1);

// ---   *   ---   *   ---

  // nit the program clock
  clknt(

    0x6000,

    L"\x01A9\x01AA\x01AB\x01AC"
    L"\x01AD\x01AE\x01AF\x01B0",

    8

  );

// ---   *   ---   *   ---

  // set further gl options
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

// ---   *   ---   *   ---
// success

  return 0;

// ---   *   ---   *   ---
// failure

  ABORT:
  fprintf(stderr,"%s\n",errme);
  SDL_Quit();return -1;

};

// ---   *   ---   *   ---

// destroy window
void windl(void) {
  SDL_DestroyWindow(win.h);
  SDL_Quit();

};

// ---   *   ---   *   ---

// busy=clock speedup signal
// render last frame
int winrend(int busy) {

  SDL_GL_SwapWindow(win.h);
  glBindFramebuffer(GL_FRAMEBUFFER,0);

  glClearColor(
    palette[0][0]*(*ambient),
    palette[0][1]*(*ambient),
    palette[0][2]*(*ambient),
    palette[0][3]*(*ambient)

  );glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  return 0;

};

// ---   *   ---   *   ---

