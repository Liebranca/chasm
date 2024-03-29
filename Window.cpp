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
    SDL_GL_CONTEXT_PROFILE_MASK,
    SDL_GL_CONTEXT_PROFILE_CORE

  );

  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MAJOR_VERSION,4

  );

  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MINOR_VERSION,5

  );

// ---   *   ---   *   ---

  // nit and catch
  if(SDL_Init(SDL_INIT_VIDEO)<0) {
    err(Win::Error::SDL_NIT,"");

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
  if(! m_handle) {

    err(
      Win::Error::WIN_OPEN,
      desc.title

    );

  } else {
    this->set_flag(Win::IS_OPEN);

  };

};

// ---   *   ---   *   ---

void Win::gl_nit(void) {

  // make gl context
  m_gl_ctx=SDL_GL_CreateContext(m_handle);

  if(!m_gl_ctx) {
    err(Win::Error::GL_CTX,"");

  };

  // nit glew
  if(glewInit()) {
    err(Win::Error::GLEW_NIT,"");

  };

// ---   *   ---   *   ---
// settings

  SDL_GL_SetSwapInterval(1);

  // set further gl options
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);

  glEnable(GL_BLEND);
  glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA

  );

};

// ---   *   ---   *   ---
// anti-cpp

void Win::nit(Win::Desc& desc) {

  this->sdl_nit();
  this->spawn(desc);
  this->gl_nit();

  // nit the program clock
  m_clk.nit(desc.fps);

  // nit the default colors
  this->set_palette(&m_pal_u[0]);

  // run further nit ruts
  this->calc_size();
  this->update_wflags();

  m_flags|=desc.flags;

};

// ---   *   ---   *   ---
// destroy window

Win::~Win(void) {

  if(m_handle != NULL) {
    SDL_DestroyWindow(m_handle);
    SDL_Quit();

  };

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
// recalculate spatial vars

void Win::calc_size(void) {

  SDL_GL_GetDrawableSize(
    m_handle,

    // ctrash
    (int*) &m_size.x,
    (int*) &m_size.y

  );

  m_hsize.x=m_size.x/2;
  m_hsize.y=m_size.y/2;

};

// ---   *   ---   *   ---
// lock/unlock cursor

void Win::disable_mouse_trap(void) {
  this->unset_flag(Win::DO_MOUSE_TRAP);
  SDL_ShowCursor(SDL_ENABLE);

};

void Win::enable_mouse_trap(void) {
  this->set_flag(Win::DO_MOUSE_TRAP);
  SDL_ShowCursor(SDL_DISABLE);

};

// ---   *   ---   *   ---
// ctrash: construc defaults

Win::Desc Win::DEFDESC={

  .title      = "CHASM",

  .width      = 640,
  .height     = 480,

  .fullscreen = false,
  .fps        = 60.0f,

  .flags      = 0x00

};

// ---   *   ---   *   ---

