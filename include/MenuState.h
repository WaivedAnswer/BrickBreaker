//MenuState.h
#ifndef _MENU_STATE_H
#define _MENU_STATE_H
#include "GameState.h"
#include "Menu.h"

//TODO create singleton
class MenuState : public GameState
{
	public:	
		MenuState();
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
		bool m_running;
		Menu* m_menu;
};
#endif
