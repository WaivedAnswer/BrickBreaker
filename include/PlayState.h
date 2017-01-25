//PlayState.h
#ifndef _PLAY_STATE_H
#define _PLAY_STATE_H
#include "GameState.h"
#include "World.h"
#include "Player.h"
#include "BrickRemover.h"
//TODO create singleton
class PlayState : public GameState
{
	public:	
		//singleton
		static PlayState* Instance();
		~PlayState();
		virtual void Init();
		virtual void Cleanup();

		virtual void Pause();
		virtual void Resume();

		virtual void Update(GameEngine* game);
		virtual void Draw(GameEngine* game);
		virtual void HandleInput(GameEngine* game);
		
		void ResetStartPositions();
		/*// inherited
		void ChangeState(GameEngine* game, GameState* state) 
		{
   			game->ChangeState(state);
  		}*/
	private:
		PlayState();
		static PlayState* m_instance;
		World* m_world;
		BrickRemover* m_bRemover;
		Player* m_player;
		Ball* m_ball;
		double m_lastClock;
		bool m_running;
};
#endif
