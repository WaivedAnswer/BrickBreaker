//BrickRemover.h
#ifndef _BRICK_REMOVER_H
#define _BRICK_REMOVER_H
#include "ObjectVisitor.h"
#include "World.h"
#include <list>
class BrickRemover : public ObjectVisitor
{
	public:
		BrickRemover(World* world);
		virtual ~BrickRemover();
		//inherited from parents but use defaults, only interested in bricks
		/*virtual void InteractActor(Actor* actor) {};
		virtual void InteractBall(Ball* ball) {};
		virtual void InteractWall(Wall* wall) {};*/
		void RemoveBricks();
		virtual void InteractBrick(Brick* brick);
	private:
		World* m_world;
		std::list<Brick*> m_removeList;
};
#endif
