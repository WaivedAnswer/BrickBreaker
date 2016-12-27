//StandardWall.h
#ifndef _STANDARD_WALL_H
#define _STANDARD_WALL_H
#include "Wall.h"

class StandardWall : public Wall
{
	public:
		StandardWall();
		//x and y centre of wall, 
		StandardWall(float hwidth, float hheight, float x, float y);
		virtual ~StandardWall();
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
