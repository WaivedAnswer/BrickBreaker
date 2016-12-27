//DeathWall.h
#ifndef _DEATH_WALL_H
#define _DEATH_WALL_H
#include "Wall.h"

class DeathWall : public Wall
{
	public:
		DeathWall();
		//x and y centre of wall, 
		DeathWall(float hwidth, float hheight, float x, float y);
		virtual ~DeathWall();
		//all inherited from base wall
		//virtual void Update(World* world);
		//virtual void Draw();
		//virtual bool CheckCollision(GameObject* other, Point& p);

		//virtual void Interact(ObjectVisitor* visitor);
		//virtual void Interact(GameObject* other);
		virtual void InteractBall(Ball* ball);
	private:
	//PhysicsBody* m_body; //inherited from base game object
};
#endif
