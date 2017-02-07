//ReadyState.cpp
#include "ReadyState.h"
#include "PlayState.h"
#include "commonSDL.h"
#include "common.h"

ReadyState* ReadyState::m_instance = nullptr;

ReadyState* ReadyState::Instance()
{
	if(m_instance == nullptr)
	{
		m_instance = new ReadyState();
	}
	return m_instance;
}

ReadyState::ReadyState()
{
	m_readyText = nullptr;

}

ReadyState::~ReadyState()
{
}

void ReadyState::Init()
{
	Cleanup();
	m_readyText = new LTexture();
	SDL_Color color = { 255, 255, 255 };
	if( !m_readyText->loadFromRenderedText( "Press Enter to Start!", color ))
	{
		printf( "Failed to render text texture!\n" );
		return;
	}
}
void ReadyState::Cleanup()
{
	if(m_readyText != nullptr)
	{
		delete m_readyText;
		m_readyText == nullptr;
	}
}

void ReadyState::Pause()
{
}
void ReadyState::Resume()
{
}

void ReadyState::Update(GameEngine* game)
{
}

void ReadyState::Draw(GameEngine* game)
{
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( gRenderer ); 

	if(m_readyText == nullptr)
	{
		return;
	}

	m_readyText->render( ( SCREEN_WIDTH - m_readyText->getWidth() )/2 , ( SCREEN_HEIGHT - m_readyText->getHeight() )/2 );

	//Update screen
	SDL_RenderPresent( gRenderer );
}
void ReadyState::HandleInput(GameEngine* game)
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
					//should have playstate underneath.
					game->PopState();
					break;
			}
		}

	}
}


