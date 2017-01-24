//NewGameCommand.cpp
#include "NewGameCommand.h"
#include "GameEngine.h"
#include "GameState.h"
#include "ReadyState.h"

NewGameCommand::NewGameCommand()
{
}
NewGameCommand::~NewGameCommand()
{
}
void NewGameCommand::Execute()
{
	GameEngine* game = GameEngine::Instance();
	if(game == nullptr)
	{
		return;
	}
	GameState* currState = game->GetCurrState();
	if(currState == nullptr)
	{
		return;
	}
	currState->ChangeState(game, new ReadyState());
}

