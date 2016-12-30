//GameEngine.h
#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H
#include "GameState.h"
#include <vector>

class GameEngine
{
	public:
		GameEngine();
		void Init();
		void Cleanup();
		
		void ChangeState(GameState* state);
		void PushState(GameState* state);
		void PopState();

		void HandleEvents();
		void Update();
		void Draw();
		
		bool Running() 
		{
			return m_running;
		}
		void Quit() 
		{
			m_running = false
		};
	
	private:
		//stack of states
		std::vector<GameState*> states;
		bool m_running;
};
#endif
