//GameEngine.cpp
#include "GameEngine.h"
#include "GameState.h"

GameEngine* GameEngine::m_instance = nullptr;

GameEngine* GameEngine::Instance() 
{
	if(m_instance == nullptr)
	{
		m_instance = new GameEngine();
	}

	return m_instance;
}
GameEngine::GameEngine()
{
	m_running = false;
	Init();
}

GameEngine::~GameEngine()
{
	Cleanup();
}
void GameEngine::Init()
{
	m_running = true;
}
void GameEngine::Cleanup()
{
	while(!states.empty())
	{
		PopState();
	}
}

void GameEngine::ChangeState(GameState* state)
{
	PopState();
	PushState(state);
}
void GameEngine::PushState(GameState* state)
{
	if(state == nullptr)
	{
		return;
	}
	if(!states.empty())
	{
		states.back()->Pause();
	}
		
	states.push_back(state);
	states.back()->Init();
}
void GameEngine::PopState()
{
	if(!states.empty())
	{
		states.back()->Cleanup();
		delete states.back();
		states.pop_back();

		if(!states.empty())
		{
			states.back()->Resume();
		}
	}
	
}

GameState* GameEngine::GetCurrState()
{
	if(!states.empty())
	{
		return states.back();
	}
	
	return nullptr;
}

void GameEngine::HandleInput()
{
	if(!states.empty())
	{
		states.back()->HandleInput(this);
	}
}
void GameEngine::Update()
{
	if(!states.empty())
	{
		states.back()->Update(this);
	}
}
void GameEngine::Draw()
{
	if(!states.empty())
	{
		states.back()->Draw(this);
	}
}

