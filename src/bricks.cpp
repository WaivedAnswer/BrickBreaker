/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/
//TODO create window class to draw to
//TODO create graphics components
//TODO create audio components
//TODO reformat to be able to use colour struct with draw application, can reuse etc.
//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "commonSDL.h"
#include "Actor.h"
#include "Ball.h"
#include "Wall.h"
#include "Brick.h"
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
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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

/*SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}*/
//move to return commands later
Directions HandleMoveInput(SDL_Event e, Actor* actor)
{
	switch( e.key.keysym.sym ) 
	{ 
		case SDLK_LEFT:
			return LEFT;
			//actor->Move(LEFT);
			break;
		case SDLK_RIGHT:
			return RIGHT;
			//actor->Move(RIGHT);
			break;
		case SDLK_UP:
			//actor->Move(UP);
			break;
		case SDLK_DOWN:
			//actor->Move(DOWN);
			break;
		default:
			break;
		
	}
	return NONE;
}

/*void BounceTest(int frames, Ball* ball)
{
	ball->Move();
	if(frames%40 ==0)
	{
		ball->Bounce(RIGHT);
	}
	else if(frames%40 ==10)
	{
		ball->Bounce(DOWN);
	}
	else if(frames%40 ==20)
	{
		ball->Bounce(LEFT);
	}
	else if(frames%40 ==30)
	{
		ball->Bounce(UP);
	}
}*/

void InitializeBrickList(std::list<Brick*> &brickList)
{
	float minX = GRID_RATIO/10.0;
	float minY = GRID_RATIO/10.0;
	float maxX = GRID_RATIO/10.0*9.0;
	float maxY = GRID_RATIO/10.0*5.0;
	//make rows
	int colCount = 8;
	int rowCount = 5;
	float brickWidth = (maxX-minX)/static_cast<float>(colCount);
	float brickHeight = (maxY-minY)/static_cast<float>(rowCount);
	for (int i = 0; i<rowCount; i++)
	{
		for (int j=0; j<colCount; j++)
		{
			brickList.push_back(new Brick(brickWidth, brickHeight, minX + brickWidth*j, minY + brickHeight*i, 10));
		}
		
	}
}

int main( int argc, char* args[] )
{
	double frameTime = 20;
	std::clock_t fbegin, fend;
	std::clock_t lastClock;
	double ftime = 0.0;
	/*WORLD = new World();
	WORLD->CreateWorld();
	BrickRemover* bRemover = new BrickRemover(WORLD);
	Player* player1= new Player();
	player1->SetActor(new Actor());

	Ball* ball = new Ball();
	ball->SetPlayer(player1);

	WORLD->Add(player1->GetActor());
	WORLD->Add(ball);*/
	int frames = 0;
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
			//Main loop flag
			bool quit = false;
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
				
				game->HandleInput();
		
				game->Update();
		
				game->Draw();

				ftime = GetTime(fbegin);
				if(ftime < frameTime)
				{
					
					SDL_Delay(frameTime - ftime);
				}

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
