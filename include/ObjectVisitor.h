//ObjectVisitor.h
#ifndef _OBJECT_VISITOR_H
#define _OBJECT_VISITOR_H
#include "Actor.h"
#include "Ball.h"
#include "Wall.h"
#include "Brick.h"
class ObjectVisitor
{
	public:
		ObjectVisitor() {};
		virtual ~ObjectVisitor() {};
		virtual void InteractActor(Actor* actor) {};
		virtual void InteractBall(Ball* ball) {};
		virtual void InteractWall(Wall* wall) {};
		virtual void InteractBrick(Brick* brick) {};
	private:
};
#endif

