//GameOverState.cpp
#include "GameOverState.h"
#include "commonSDL.h"
#include "common.h"
#include "MenuState.h"
#include "PlayState.h"

GameOverState* GameOverState::m_instance = nullptr;

GameOverState* GameOverState::Instance()
{
	if(m_instance == nullptr)
	{
		m_instance = new GameOverState();
	}
	return m_instance;
}

GameOverState::GameOverState()
{
	m_gameOverText = nullptr;
	m_instructionsText = nullptr;

}

GameOverState::~GameOverState()
{
}

void GameOverState::Init()
{
	if(m_gameOverText == nullptr)
	{
		m_gameOverText = new LTexture();
	}
	if(m_instructionsText == nullptr)
	{
		m_instructionsText = new LTexture();
	}
	SDL_Color color = { 255, 255, 255 };
	if(m_didWin)
	{
		if( !m_gameOverText->loadFromRenderedText( "YOU WIN!", color ))
		{
			printf( "Failed to render gameOver texture!\n" );
			return;
		}
	}
	else
	{
		if( !m_gameOverText->loadFromRenderedText( "GAME OVER", color ))
		{
			printf( "Failed to render gameOver texture!\n" );
			return;
		}
	}
	if( !m_instructionsText->loadFromRenderedText( "Press N for new game or M for menu", color ))
	{
		printf( "Failed to render instructions texture!\n" );
		return;
	}
}
void GameOverState::Cleanup()
{
	if(m_gameOverText != nullptr)
	{
		delete m_gameOverText;
		m_gameOverText = nullptr;
	
	}
	if(m_instructionsText != nullptr)
	{
		delete m_instructionsText;
		m_instructionsText = nullptr;
	}
}

void GameOverState::Pause()
{
}
void GameOverState::Resume()
{
}

void GameOverState::Update(GameEngine* game)
{
}

void GameOverState::Draw(GameEngine* game)
{
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( gRenderer ); 

	if(m_gameOverText != nullptr)
	{
		m_gameOverText->render( ( SCREEN_WIDTH - m_gameOverText->getWidth() )/2 , ( SCREEN_HEIGHT - m_gameOverText->getHeight() )/3 );
	}
	if(m_instructionsText != nullptr)
	{
		m_instructionsText->render( ( SCREEN_WIDTH - m_instructionsText->getWidth() )/2 , ( SCREEN_HEIGHT - m_instructionsText->getHeight() )*2/3 );
	}


	//Update screen
	SDL_RenderPresent( gRenderer );
}
void GameOverState::HandleInput(GameEngine* game)
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
				case SDLK_m:
					game->ChangeState(MenuState::Instance());
					break;
				case SDLK_n:
					game->ChangeState(PlayState::Instance());
					break;
			}
		}

	}
}

void GameOverState::SetWin(bool win)
{
	m_didWin = win;
}


