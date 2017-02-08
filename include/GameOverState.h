//GameOverState.h
#ifndef _GAME_OVER_STATE_H
#define _GAME_OVER_STATE_H
#include "GameState.h"
#include "LTexture.h"
#include <string>

//State to be used at end of game 
//Set whether it was win or not using SetWin before changing game state,
//If not singleton suggest using constructor
class GameOverState : public GameState
{
	public:
		//singleton
		static GameOverState* Instance();
		~GameOverState();

		virtual void Init();
		virtual void Cleanup();

		virtual void Pause();
		virtual void Resume();

		virtual void Update(GameEngine* game);
		virtual void Draw(GameEngine* game);
		virtual void HandleInput(GameEngine* game);
		void SetWin(bool win);
		//inherited from GameState
		//void ChangeState(GameEngine* game, GameState* state) 

	private:
		GameOverState();
		static GameOverState* m_instance;
		bool m_didWin;
		LTexture* m_gameOverText;
		LTexture* m_instructionsText;
};
#endif

