//MenuState.h
#ifndef _MENU_STATE_H
#define _MENU_STATE_H
#include "GameState.h"
#include "Menu.h"

class MenuState : public GameState
{
	public:	
		//singleton
		static MenuState* Instance();
		~MenuState();
		virtual void Init();
		virtual void Cleanup();

		virtual void Pause();
		virtual void Resume();

		virtual void Update(GameEngine* game);
		virtual void Draw(GameEngine* game);
		virtual void HandleInput(GameEngine* game);

		/*// inherited
		void ChangeState(GameEngine* game, GameState* state) 
		{
   			game->ChangeState(state);
  		}*/
	private:
		MenuState();
		static MenuState* m_instance;
		bool m_running;
		Menu* m_menu;
};
#endif
