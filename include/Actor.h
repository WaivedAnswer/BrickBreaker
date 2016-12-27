//Actor.h
#ifndef _ACTOR_H
#define _ACTOR_H

#include "GameObject.h"
#include "common.h"
#include "Player.h"

class Actor : public GameObject
{
	public:
		Actor();
		Actor(float dimensions[2], float position[2], bool canMove, float speed);
		Actor(PhysicsBody* body, bool canMove);
		virtual ~Actor();

		virtual void Update(World* world, double lastClock);
		virtual void Draw();
		virtual bool CheckCollision(GameObject* other, Point& p);

		virtual void Interact(ObjectVisitor* visitor);
		virtual void Interact(GameObject* other);
		virtual void InteractBall(Ball* other);

		//inherited from base
		//void SetPhysicsBody(PhysicsBody* body) {m_body = body;};
		//PhysicsBody* GetPhysicsBody() {return m_body;};

		//add world reference
		void SetDirection(Directions direction);
		void Move(double lastClock);
		void UnMove(double lastClock);
		void SetCanMove(bool canMove);
		Player* GetPlayer();
		void SetPlayer(Player* player);
	private:
		//PhysicsBody* m_body; //inherited from base
		//eventually add player*
		Player* m_player;
		float m_speed;
		bool m_canMove;
		
};
#endif
