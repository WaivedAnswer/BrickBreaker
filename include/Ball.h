//Ball.h
#ifndef _BALL_H
#define _BALL_H
#include "GameObject.h"
#include "common.h"
#include "Player.h"
//TODO maybe make the visitor/interactor separate from ball, just get reference to ball and interact items with it

class Ball : public GameObject
{
	public:
		Ball();
		Ball(float startSpeed, float startAngle);
		virtual ~Ball();

		virtual void Update(World* world, double lastClock);
		virtual void Draw();

		virtual bool CheckCollision(GameObject* other, Point& p);

		virtual void Interact(ObjectVisitor* visitor);
		virtual void Interact(GameObject* other);
		//not sure if needed just now?
		virtual void InteractBrick(Brick* brick);
		virtual void InteractActor(Actor* actor);

		//to be implemented with command later
		void Move(double lastClock);
		void UnMove(double lastClock);
		void SetCanMove(bool canMove);
		Player* GetPlayer();
		void SetPlayer(Player* player);
	private:
		//PhysicsBody* m_body; //inherited from base
		//eventually add player*
		bool m_canMove;
		float m_speed;
		float m_angle;
		Player* m_player;
		GameObject* lastCollision;
};

#endif
