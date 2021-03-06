//GameState.h
#ifndef _GAME_STATE_H
#define _GAME_STATE_H
#include "GameEngine.h"

class GameState
{
	public:
		virtual ~GameState()
		{
		}
		virtual void Init() = 0;
		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void Update(GameEngine* game) = 0;
		virtual void Draw(GameEngine* game) = 0;
		virtual void HandleInput(GameEngine* game) = 0;

		void ChangeState(GameEngine* game, GameState* state) 
		{
   			game->ChangeState(state);
  		}
		
		
	protected:
		GameState()
		{
		}
};
#endif
