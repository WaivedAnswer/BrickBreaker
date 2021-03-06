//PlayState.cpp
#include "PlayState.h"
#include <SDL2/SDL.h>
#include "commonSDL.h"
#include <ctime>
#include "LTexture.h"
PlayState::PlayState()
{
	m_running = false;
	m_world = nullptr;
	m_bRemover = nullptr;
	m_player = nullptr;
	
}
PlayState::~PlayState()
{
	Cleanup();
}
void PlayState::Init()
{
	Cleanup();
	m_running = true;
	m_world = new World();
	if(m_world == nullptr)
	{
		return;
	}
	m_world->CreateWorld();
	m_bRemover = new BrickRemover(m_world);

	m_player = new Player();

	if(m_player != nullptr)
	{
		Actor* actor = new Actor();
		m_player->SetActor(actor);
		m_world->Add(actor);
	}

	Ball* ball = new Ball();
	if(ball != nullptr)
	{
		ball->SetPlayer(m_player);
		m_world->Add(ball);
	}

	m_lastClock = clock();
}
void PlayState::Cleanup()
{
	if(m_world != nullptr)
	{
		delete m_world;
		m_world = nullptr;
	}
	if(m_player != nullptr)
	{
		delete m_player;
		m_player = nullptr;
	}

	if(m_bRemover != nullptr)
	{
		delete m_bRemover;
		m_bRemover = nullptr;
	}
	m_running = false;
}

void PlayState::Pause()
{
	m_running = false;
}
void PlayState::Resume()
{
	m_running = true;
}

void PlayState::Update(GameEngine* game)
{
	if(m_running)
	{
		//TODO change to real time
		//get time from engine?
		if(m_world != nullptr)
		{
			m_world->Update(m_lastClock);
			m_lastClock = clock();
		}
		if(m_bRemover != nullptr)
		{
			m_bRemover->RemoveBricks();
		}
	}

}
void PlayState::Draw(GameEngine* game)
{
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( gRenderer ); 
	if(m_world != nullptr)
	{
		m_world->Draw();
	}
	if(m_player != nullptr)
	{
		//Rendered texture
		LTexture scoreTexture;
		LTexture livesTexture;
		SDL_Color color = { 255, 255, 255 };
		if( !scoreTexture.loadFromRenderedText( "SCORE: " + std::to_string(m_player->GetScore()), color ) )
		{
			printf( "Failed to render text texture!\n" );
			return;
		}
		scoreTexture.render( ( SCREEN_WIDTH - scoreTexture.getWidth() ) , static_cast<float>(SCREEN_HEIGHT)/4.0 );

		if( !livesTexture.loadFromRenderedText( "LIVES: " + std::to_string(m_player->GetLives()), color ) )
		{
			printf( "Failed to render text texture!\n" );
			return;
		}
		livesTexture.render( ( SCREEN_WIDTH - livesTexture.getWidth() ), static_cast<float>(SCREEN_HEIGHT)*3.0/4.0 );
	}
	//Update screen
	SDL_RenderPresent( gRenderer );
}
//TODO move away from SDL input here
void PlayState::HandleInput(GameEngine* game)
{
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			game->Quit();
		}
		if(m_player != nullptr)
		{
			m_player->HandleInput(e);
		}
	}
}
