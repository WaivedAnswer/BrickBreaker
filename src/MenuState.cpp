//MenuState.cpp
#include "MenuState.h"
#include "PlayState.h"
#include <SDL2/SDL.h>
#include "commonSDL.h"
#include "CompositeNode.h"
#include "ActionNode.h"
#include "NewGameCommand.h"
MenuState::MenuState()
{
	m_running = false;
	m_menu = nullptr;
}
MenuState::~MenuState()
{
	Cleanup();
}

void CreateTestMenu(Menu* menu)
{
	if ( menu == nullptr)
	{
		menu = new Menu();
	}

	ActionNode* play = new ActionNode("Play");
	play->SetAction(new NewGameCommand());
	menu->Add(play);

	CompositeNode* settings = new CompositeNode("Settings");
	if( settings != nullptr)
	{
		settings->Add(new CompositeNode("Music"));
		//TODO add third type of menu node for slider
		settings->Add(new ActionNode("Speed"));
	}
	menu->Add(settings);

	menu->Add(new ActionNode("Credits"));
}
void MenuState::Init()
{
	//Cleanup();
	m_menu = new Menu();
	CreateTestMenu(m_menu);
	m_running = true;
	
}
void MenuState::Cleanup()
{
	if(m_menu != nullptr)
	{
		delete m_menu;
		m_menu = nullptr;
	}
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
	//std::cout << m_menu;
	if(m_menu != nullptr)
	{
		m_menu->Display();
	}
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
		/*else if (e.type == SDL_KEYDOWN)
		{
			switch( e.key.keysym.sym ) 
			{
				case SDLK_RETURN:
					ChangeState(game, new PlayState());
					break;
			}
		}*/
		if(m_menu != nullptr)
		{
			m_menu->HandleInput(e);
		}
		//new way to handle input?

	}
}
