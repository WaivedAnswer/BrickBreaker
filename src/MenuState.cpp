//MenuState.cpp
#include "MenuState.h"
#include "PlayState.h"
#include <SDL2/SDL.h>
#include "commonSDL.h"
MenuState::MenuState()
{
	m_running = false;
	
}
MenuState::~MenuState()
{
	Cleanup();
}
void MenuState::Init()
{
	Cleanup();
	m_running = true;
	
}
void MenuState::Cleanup()
{
	m_running = false;
}

void MenuState::Pause()
{
	m_running = false;
}
void MenuState::Resume()
{
	m_running = true;
}

void MenuState::Update(GameEngine* game)
{
	//menu->Update?

}
void MenuState::Draw(GameEngine* game)
{
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( gRenderer ); 
	
	//menu->Draw();
	//Update screen
	SDL_RenderPresent( gRenderer );
}
//TODO move away from SDL input here
void MenuState::HandleInput(GameEngine* game)
{
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			game->Quit();
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch( e.key.keysym.sym ) 
			{
				case SDLK_RETURN:
					ChangeState(game, new PlayState());
					break;
			}
		}
		//new way to handle input?

	}
}
