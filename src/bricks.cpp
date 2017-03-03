/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/
//TODO create window class to draw to
//TODO create graphics components
//TODO create audio components
//TODO reformat to be able to use colour struct with draw application, can reuse etc.
//Using SDL, SDL_image, standard IO, math, and strings
#include <stdio.h>
#include <string>
#include <cmath>
#include "commonSDL.h"
#include "Actor.h"
#include "Ball.h"
#include "Wall.h"
#include "PhysicsBody.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include "World.h"
#include "Player.h"
#include "BrickRemover.h"
#include "PlayState.h"
#include "MenuState.h"
#include "ReadyState.h"
#include "GameEngine.h"
#include <iostream>
#include <list>
#include <ctime>

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;
World* WORLD = nullptr;
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "BrickBreaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
                
                //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "assets/Roboto-Bold.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}





int main( int argc, char* args[] )
{
	double frameTime = 20;
    std::clock_t fbegin;
	double ftime = 0.0;
    
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			GameEngine* game = GameEngine::Instance();
			if(game == nullptr)
			{
				std::cout <<"Error, Error";
				return -1;
			}

			MenuState* menu = MenuState::Instance();
			if(menu == nullptr)
			{
				std::cout << "Error, Error";
				return -1;
			}
			game->PushState(menu);

			//While application is running
			while( game->Running() )
			{
				
				fbegin = clock();
				do
				{
					game->HandleInput();
					game->Update();
					ftime = GetTime(fbegin);
				} while(ftime < frameTime);
				game->Draw();
			}
			delete game;
		}
	}
	
	//Free resources and close SDL
	close();
	//delete actor;
	//delete ball;
	return 0;
}
