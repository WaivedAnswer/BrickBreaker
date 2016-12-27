//Brick.h
#ifndef _BRICK_H
#define _BRICK_H
#include "GameObject.h"
class Brick : public GameObject
{
	public:
		Brick();
		Brick(float width, float height, float x, float y, int pointVal);
		virtual ~Brick();

		virtual void Update(World* world, double lastClock);
		virtual void Draw();
		//should be stationary for the moment, don't need collision checking
		virtual bool CheckCollision(GameObject* other, Point& p);

		virtual void Interact(ObjectVisitor* visitor);
		virtual void Interact(GameObject* other);
		virtual void InteractBall(Ball* ball);

		void HitBrick();
		int GetHealth();
		int GetPointValue();
	private:
		//PhysicsBody* m_body; //inherited from base
		int m_pointVal;
		int m_health;
		
};
#endif
