//PhysicsBody.h
#ifndef _PHYSICS_BODY_H
#define _PHYSICS_BODY_H
#include "common.h"
#include "Collider.h"
class PhysicsBody
{
	public:
		//position from collider?
		//collider position gets overriden by body position
		PhysicsBody(Collider* collider, Vector velocity, Point position, bool isKinematic);
		~PhysicsBody();

		//p is set to point on other closest to body centre
		bool CheckCollision(PhysicsBody* other, Point& p);
		
		void HandleCollision(PhysicsBody* other, const Point& p);

		void Move(float time);
		void UnMove(float time);
		
		Collider* GetCollider();

		Vector GetVelocity();
		void SetVelocity(const Vector& velocity);

		//set and return centre position
		void SetPosition(const Point& posit);
		Point GetPosition();
		//from collider
		void GetDimensions(float (&dimensions)[COORDNUM]);

		bool IsKinematic();
		void SetKinematic(bool isKinematic);

	private:
		Collider* m_collider;
		Vector m_velocity;
		Point m_position;
		bool m_isKinematic;
};	
#endif
