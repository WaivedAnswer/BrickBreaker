//Wall.h
#ifndef _WALL_H
#define _WALL_H
#include "GameObject.h"

class Wall : public GameObject
{
	public:
		Wall();
		//x and y centre of wall, 
		Wall(float hwidth, float hheight, float x, float y);

		virtual void Update(World* world, double lastClock);
		virtual void Draw();
		virtual bool CheckCollision(GameObject* other, Point& p);

		virtual void Interact(ObjectVisitor* visitor);
		virtual void Interact(GameObject* other);
		virtual void InteractBall(Ball* ball);
	protected: 
		virtual ~Wall() = 0;
	private:
	//PhysicsBody* m_body; //inherited from base
};
#endif
