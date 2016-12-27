//Command.h
#ifndef _COMMAND_H
#define _COMMAND_H
//TODO flesh out later
class Command
{
	public:
		virtual ~Command() {};
		virtual void Execute() = 0;
	protected:
		Command() {};
};
#endif
