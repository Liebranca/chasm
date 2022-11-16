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

  #include <iostream>
  #include <GL/glew.h>

  #include "Window.hpp"

// ---   *   ---   *   ---
// translates i32 color buffer to float

void Win::set_palette(
  uint32_t* src

) {

  for(int c=0;c<16;c++) {
    for(int i=24,j=c*4;i>0;i-=8,j++) {

      uint32_t x=(*src>>i)&0xFF;
      m_pal[j]=x/255.0;

    };

    src++;

  };

};

// ---   *   ---   *   ---
// init boiler

void Win::sdl_nit(void) {

  // set gl attributes
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE,4);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,4);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,4);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,4);

  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,16);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  SDL_GL_SetAttribute(
    SDL_GL_ACCELERATED_VISUAL,1

  );

  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MAJOR_VERSION,4

  );

  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MINOR_VERSION,6

  );

  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_PROFILE_MASK,
    SDL_GL_CONTEXT_PROFILE_CORE

  );

  // nit and catch
  if(SDL_Init(SDL_INIT_VIDEO)<0) {
    evil_throw(Win::Error::SDL_NIT,"");

  };

};

// ---   *   ---   *   ---
// makes a new

void Win::spawn(Win::Desc& desc) {

  // spawn the window
  m_handle=SDL_CreateWindow(

    desc.title.c_str(),

    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,

    desc.width,
    desc.height,

    SDL_WINDOW_OPENGL
  | SDL_WINDOW_BORDERLESS

  | (SDL_WINDOW_FULLSCREEN_DESKTOP*desc.fullscreen)

  );

  // catch
  if(!m_handle) {

    evil_throw(
      Win::Error::WIN_OPEN,
      desc.title

    );

  } else {
    this->set_flag(Win::isOpen);

  };

};

// ---   *   ---   *   ---

void Win::gl_nit(void) {

  // make gl context
  m_gl_ctx=SDL_GL_CreateContext(m_handle);

  if(!m_gl_ctx) {
    evil_throw(Win::Error::GL_CTX,"");

  };

  // nit glew
  if(glewInit()) {
    evil_throw(Win::Error::GLEW_NIT,"");

  };

// ---   *   ---   *   ---
// settings

  SDL_GL_SetSwapInterval(1);

  // set further gl options
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_DEPTH_TEST);

// we don't need this one right now
// keeping it around for when we do ;>
  glDisable(GL_CULL_FACE);
//  glCullFace(GL_BACK);

  glEnable(GL_BLEND);
  glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA

  );

};

// ---   *   ---   *   ---
// spawns a window

Win::Win(Win::Desc& desc) {

  this->sdl_nit();
  this->spawn(desc);
  this->gl_nit();

  // nit the program clock
  m_clk.nit(desc.fps);

  // nit the default colors
  this->set_palette(&m_pal_u[0]);

};

// ---   *   ---   *   ---
// destroy window

Win::~Win(void) {
  SDL_DestroyWindow(m_handle);
  SDL_Quit();

};

// ---   *   ---   *   ---
// busy=clock speedup signal
// render last frame

void Win::refresh(int busy) {

  SDL_GL_SwapWindow(m_handle);
  glBindFramebuffer(GL_FRAMEBUFFER,0);

  glClearColor(
    m_pal[m_amc+0] * m_amx,
    m_pal[m_amc+1] * m_amx,
    m_pal[m_amc+2] * m_amx,
    m_pal[m_amc+3] * m_amx

  );

  glClear(
    GL_COLOR_BUFFER_BIT
  | GL_DEPTH_BUFFER_BIT

  );

  m_clk.tick(busy);

};

// ---   *   ---   *   ---
// ctrash: construc defaults

Win::Desc Win::DEFDESC={

  .title      = "CHASM",

  .width      = 640,
  .height     = 480,

  .fullscreen = false,
  .fps        = 60.0f

};

// ---   *   ---   *   ---

