//GameObject.h
#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H
#include "PhysicsBody.h"
#include "World.h"
#include "common.h"
class ObjectVisitor;
class Actor;
class Ball;
class Brick;
class Wall;

class GameObject
{
	public:
		GameObject() {};
		virtual ~GameObject() 
		{
			if (m_body != nullptr)
			{
				delete m_body;
				m_body = nullptr;
			}
		}
		virtual void Update(World* world, double lastClock) = 0;
		virtual void Draw() = 0;

		//debating moving this to protected:
		virtual bool CheckCollision(GameObject* other, Point& p) = 0;

		void SetPhysicsBody(PhysicsBody* body) {m_body = body;};
		PhysicsBody* GetPhysicsBody() {return m_body;};
		//todo overwrite to get things from physics bodies
		//USELESS
		float* const GetDimensions() {return m_dimensions;};
		void SetDimensions(float dimensions[2]) 
		{
			for(int i =0; i < 2; i++)
			{
				m_dimensions[i] = dimensions[i];
			}
		}
		Point const GetPosition() {return m_position;};
		void SetPosition(Point position)
		{
			m_position = position;
		}
		virtual void Interact(ObjectVisitor* visitor) = 0;

		virtual void Interact(GameObject* other) = 0;
		virtual void InteractActor(Actor* other) {};
		virtual void InteractBall(Ball* ball) {};
		virtual void InteractBrick(Brick* brick) {};
		virtual void InteractWall(Wall* wall) {};
	protected:
		PhysicsBody* m_body;
		float m_dimensions[2];
		Point m_position;
		
};
#endif
