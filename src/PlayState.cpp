//PlayState.cpp
#include "PlayState.h"
#include <SDL2/SDL.h>
#include "commonSDL.h"
#include <ctime>
#include "LTexture.h"
#include "ReadyState.h"
#include "GameEngine.h"
#include "MenuState.h"
#include "GameOverState.h"
#include <limits>

PlayState* PlayState::m_instance = nullptr;

PlayState* PlayState::Instance()
{
	if(m_instance == nullptr)
	{
		m_instance = new PlayState();
	}
	return m_instance;
}

PlayState::PlayState()
{
	m_running = false;
	m_world = nullptr;
	m_bRemover = nullptr;
	m_player = nullptr;
	m_ball = nullptr;
    m_musicSource = nullptr;
	m_lastClock = 0;
	m_pauseTimer = 0;
    
	
}
PlayState::~PlayState()
{
	Cleanup();
}
void PlayState::Init()
{
	Cleanup();
	m_running = false;
	m_world = new World();
	if(m_world == nullptr)
	{
		return;
	}
	//m_world->CreateWorld();
    m_world->CreateWorld("assets/Level0_2.json");
	m_bRemover = new BrickRemover(m_world);

	m_player = new Player();

	if(m_player != nullptr)
	{
		Actor* actor = new Actor();
		m_player->SetActor(actor);
		m_world->Add(actor);
	}

	m_ball = new Ball();
	if(m_ball != nullptr)
	{
		m_ball->SetPlayer(m_player);
		m_world->Add(m_ball);
	}

	GameEngine* game = GameEngine::Instance();
	if(game == nullptr)
	{
		std::cout << "Error, Error";
		return;
	}
    
    m_musicSource = new AudioSource();
    if(m_musicSource != nullptr)
    {
        m_musicSource->LoadClipFromFile("assets/pacman_intro.wav" , CLIP_MUSIC);
        m_musicSource->Play(-1, 0.20);
    }
    
	//game->PushState(ReadyState::Instance());
	m_pauseTimer = PREPLAY_PAUSE;
	m_lastClock = static_cast<double>(clock());
    

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
    
    if(m_musicSource != nullptr)
    {
        m_musicSource->Stop();
        delete m_musicSource;
        m_musicSource = nullptr;

    }
	m_running = false;
}

void PlayState::Pause()
{
	m_pauseTimer = std::numeric_limits<double>::max();
	m_running = false;
}
void PlayState::Resume()
{
	//m_running = true;
	m_lastClock = static_cast<double>(clock());
	m_pauseTimer = PREPLAY_PAUSE;
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
			m_lastClock = static_cast<double>(clock());
		}
		if(m_bRemover != nullptr)
		{
			m_bRemover->RemoveBricks();
			if(m_bRemover->GetBrickCount()<=0)
			{
				GameOverState::Instance()->SetWin(true);
				game->ChangeState(GameOverState::Instance());
			}
		}
		if(m_player != nullptr)
		{
			if(m_player->GetLives() <=0)
			{
				GameOverState::Instance()->SetWin(false);
				game->ChangeState(GameOverState::Instance());
			}
		}
	}
	else
	{
		m_pauseTimer -= GetTime(m_lastClock);
		//just clock to keep time
		m_lastClock = static_cast<double>(clock());
		if(m_pauseTimer <= 0)
		{
			m_running = true;
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
		if( !scoreTexture.loadFromRenderedText( "SCORE:" + std::to_string(m_player->GetScore()), color ) )
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
		else if(e.type == SDL_KEYDOWN)
		{
			switch( e.key.keysym.sym ) 
			{ 
				case SDLK_p:
					if(m_running)
					{
						Pause();
					}
					else
					{
						Resume();
					}
					
					break;
				case SDLK_r:
					game->ChangeState(GameOverState::Instance());
			}
		}
		if(m_player != nullptr)
		{
			m_player->HandleInput(e);
		}
	}
}

void PlayState::ResetStartPositions()
{
	m_pauseTimer = PREPLAY_PAUSE;
	m_running = false;
	if(m_ball != nullptr)
	{
		PhysicsBody* ballBody = m_ball->GetPhysicsBody();
		if(ballBody != nullptr)
		{
			ballBody->SetPosition(DEFAULT_BALL_POS);
			ballBody->SetVelocity(DEFAULT_BALL_SPEED * Vector(cos(DEFAULT_BALL_ANGLE),-sin(DEFAULT_BALL_ANGLE)));
		}
		
		
	}
	if(m_player != nullptr)
	{
		Actor* actor = m_player->GetActor();
		if(actor != nullptr)
		{
			PhysicsBody* actorBody = actor->GetPhysicsBody();
			if(actorBody != nullptr)
			{
				actorBody->SetPosition(DEFAULT_ACTOR_POS);
			}
		}
	}
}
