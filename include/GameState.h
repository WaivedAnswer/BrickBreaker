//GameState.h
#ifndef _GAME_STATE_H
#define _GAME_STATE_H

class GameEngine;

class GameState
{
	public:
		~GameState();
		virtual void Init() = 0;
		virtual void Cleanup() = 0;

		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void HandleInput() = 0;

		void ChangeState(GameEngine* game, GameState* state) 
		{
   			game->ChangeState(state);
  		}
		
		
	protected:
		GameState();
};
#endif
