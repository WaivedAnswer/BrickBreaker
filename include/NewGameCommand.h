//NewGameCommand.h
#ifndef _NEW_GAME_COMMAND_H
#define _NEW_GAME_COMMAND_H
#include "Command.h"
//#include "GameState.h"

class NewGameCommand : public Command
{
	public:
		NewGameCommand();
		~NewGameCommand();
		virtual void Execute();
	private:
		//I think we should access this using game engine at time of execute
		//GameState* m_currState;
};
#endif
