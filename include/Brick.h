//Brick.h
#ifndef _BRICK_H
#define _BRICK_H
#include "GameObject.h"
#include "LTexture.h"
class Brick : public GameObject
{
	public:

		virtual ~Brick();

		virtual void Update(World* world, double lastClock) = 0;
		virtual void Draw() = 0;
    
		//should be stationary for the moment, don't need collision checking
        virtual bool CheckCollision(GameObject* other, Point& p);
        //default implementation of double dispatch interaction
		virtual void Interact(ObjectVisitor* visitor);
		virtual void Interact(GameObject* other);
    
		virtual void InteractBall(Ball* ball) = 0;

		virtual void HitBrick() = 0;
		virtual int GetHealth() = 0;
		virtual int GetPointValue() = 0;
    
    protected:
        Brick();
        Brick(float width, float height, float x, float y, int pointVal);
		//PhysicsBody* m_body; //inherited from GameObject
		
};
#endif
