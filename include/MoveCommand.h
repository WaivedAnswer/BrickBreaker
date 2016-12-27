//MoveCommand.h
#ifndef _MOVE_COMMAND_H
#define _MOVE_COMMAND_H
#include "Command.h"
#include "Actor.h"
#include "common.h"
class MoveCommand : public Command
{
	public:
		MoveCommand(Actor* actor, double time, Directions direction);
		~MoveCommand();
		virtual void Execute();
	private:
		Actor* m_actor;
		double m_time;
		Directions m_direction;
};
#endif
