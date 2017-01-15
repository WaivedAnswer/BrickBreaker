//GameEngine.h
#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H
#include <vector>

class GameState;

class GameEngine
{
	public:
		static GameEngine* Instance();
		~GameEngine();

		void Init();
		void Cleanup();
		
		void ChangeState(GameState* state);
		void PushState(GameState* state);
		void PopState();
		GameState* GetCurrState();
		

		void HandleInput();
		void Update();
		void Draw();

		
		bool Running() 
		{
			return m_running;
		}
		void Quit() 
		{
			m_running = false;
		}

	protected:
		GameEngine();
	private:
		// Don't Implement
		GameEngine(GameEngine const&);
		void operator=(GameEngine const&);

		static GameEngine* m_instance;
		//stack of states
		std::vector<GameState*> states;
		bool m_running;
};
#endif
