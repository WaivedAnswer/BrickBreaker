//ActionNode.cpp
#include "ActionNode.h"

ActionNode::ActionNode(std::string name) : MenuNode(name)
{
	m_command = &m_nullCommand;
}
ActionNode::~ActionNode()
{
	if(m_command != nullptr && m_command != &m_nullCommand)
	{
		delete m_command;
		m_command = nullptr;
	}
}

void ActionNode::SetAction(Command* command)
{
	if(command != nullptr)
	{
		m_command = command;
	}
	else
	{
		m_command = &m_nullCommand;
	}
}

void ActionNode::Display()
{
}

//selects current node
void ActionNode::Select(Menu* menu)
{
	m_command->Execute();
}
