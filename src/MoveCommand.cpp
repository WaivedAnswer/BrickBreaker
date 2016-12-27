//MoveCommand.cpp
#include "MoveCommand.h"
MoveCommand::MoveCommand(Actor* actor, double time, Directions direction)
{
	m_actor = actor;
	m_time = time;
	m_direction = direction;
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{
	if(m_actor != nullptr)
	{
		m_actor->SetDirection(m_direction);
		//m_actor->Move(m_time);
	}
}

