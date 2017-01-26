//ReadyState.h
#ifndef _READY_STATE_H
#define _READY_STATE_H
#include "GameState.h"
#include "LTexture.h"

//State to be used at start of new game
class ReadyState : public GameState
{
	public:
		//singleton
		static ReadyState* Instance();
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
		ReadyState();
		static ReadyState* m_instance;
		LTexture* m_readyText;

};
#endif
