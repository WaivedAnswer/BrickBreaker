//MenuNode.h
#ifndef _MENU_NODE_H
#define _MENU_NODE_H
#include <string>
#include "Menu.h"
class MenuNode
{
	public:
		virtual ~MenuNode() {};
		//add and remove nodes to tree
		virtual void Display() = 0;
		//selects current node
		virtual void Select(Menu* menu) = 0;

		virtual void Add(MenuNode* node) {};
		virtual void Remove(MenuNode* node) {};
		virtual void SelectNext() {};
		virtual void SelectPrev() {};
		virtual MenuNode* GetCurrSelection() 
		{ 
			return nullptr;
		}
		virtual int GetChildCount()
		{
			return 0;
		}

		std::string GetName()
		{
			return m_name;
		}
		
	protected:
		MenuNode(std::string name): m_name(name) {};
		

	private:
		std::string m_name;
};	
#endif
