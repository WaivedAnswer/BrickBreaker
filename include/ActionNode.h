//ActionNode.h
#ifndef _ACTION_NODE_H
#define _ACTION_NODE_H
#include "MenuNode.h"
#include <string>
#include "Command.h"
#include "NullCommand.h"

//menu node that triggers an action or event in menu (leaf nodes of menu) 
//selecting causes and action to occur
class ActionNode : public MenuNode
{
	public:
		ActionNode(std::string name);
		~ActionNode();

		void SetAction(Command* command);

		virtual void Display();

		//selects current node
		virtual void Select(Menu* menu);

		//inherited from MenuNode along with name
		/*
		std::string GetName()
		{
			return m_name;
		}
		*/
	private:
		Command* m_command;
		NullCommand m_nullCommand;
};
#endif
