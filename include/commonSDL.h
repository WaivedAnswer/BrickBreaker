//commonSDL.h
#ifndef _COMMON_SDL_H
#define _COMMON_SDL_H
#ifdef __linux__
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#elif __APPLE__
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#endif


//SDL related
const float GRID_RATIO = 100;
const float SCREEN_WIDTH = 640;
const float SCREEN_HEIGHT = 480;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Globally used font
extern TTF_Font *gFont;

#endif
