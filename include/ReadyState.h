//ReadyState.h
#ifndef _READY_STATE_H
#define _READY_STATE_H
#include "GameState.h"
#include "LTexture.h"
#include "World.h"

//State to be used at start of new game and after life has been lost, should reset player and ball position but maintain world
class ReadyState : public GameState
{
	public:
		ReadyState();
		~ReadyState();

		virtual void Init();
		virtual void Cleanup();

		virtual void Pause();
		virtual void Resume();

		virtual void Update(GameEngine* game);
		virtual void Draw(GameEngine* game);
		virtual void HandleInput(GameEngine* game);

		//inherited from GameState
		//void ChangeState(GameEngine* game, GameState* state) 

	private:
		LTexture* m_readyText;

};
#endif

