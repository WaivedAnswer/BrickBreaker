//commonSDL.h
#ifndef _COMMON_SDL_H
#define _COMMON_SDL_H
#include "SDL2/SDL.h"

//SDL related
const float GRID_RATIO = 100;
const float SCREEN_WIDTH = 640;
const float SCREEN_HEIGHT = 480;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;
#endif
