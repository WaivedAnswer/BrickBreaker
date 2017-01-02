//GameEngine.cpp
#include "GameEngine.h"
#include "GameState.h"

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

