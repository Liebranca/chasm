#ifndef __WINDOW_H__
#define __WINDOW_H__

#ifdef __cplusplus
extern "C" {
#endif

// ---   *   ---   *   ---

// sets pointers to palette and ambient factor
void wingrefs(float** pal,float* am);

// creates window
int winnt(
  const char* title,
  int width,
  int height,
  int fullscreen

);

// destroys window
void windl(void);

// loop top
int winrend(int busy);

// ---   *   ---   *   ---

#ifdef __cplusplus
};
#endif

#endif // __WINDOW_H__

