//Menu.h
#ifndef _MENU_H
#define _MENU_H
#include "SDL2/SDL.h"
#include <vector>
class MenuNode;
//Menu class to be used with the menu state, contains MenuNode Items
//definitely will want some sort of builder design pattern to create this
class Menu
{
	public:
		Menu();
		~Menu();

		//handles keyboard input for menustate
		void HandleInput(SDL_Event& e);

		//adds menu node to root
		void Add(MenuNode* node);
		//removes menu node from root
		//or children if node doesn't exist at top level
		void Remove(MenuNode* node);
		//sets current node
		void SetCurrent(MenuNode* node);
		//pops current node, sets parent node as current
		void PopCurrent();
		//displays current menu subset
		void Display();
		
	private:
		//MenuNodes
		MenuNode* m_root;
		//used to determine which ancestry path has been selected
		//alternative would be to have each node know its parent and
		//backtrack to parent node
		std::vector<MenuNode*> m_selectionStack;
		
};
#endif
