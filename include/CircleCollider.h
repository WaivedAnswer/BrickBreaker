//CircleCollider.h
#ifndef _CIRCLE_COLLIDER_H
#define _CIRCLE_COLLIDER_H
#include "Collider.h"
#include "common.h"

class CircleCollider : public Collider
{
	public:
		CircleCollider(Point centre, float radius);
		virtual ~CircleCollider();

		//generic collision call
		virtual bool CheckCollision(Collider* other, Point& p);

		//specific collision calls
		virtual bool CheckCollisionCircle(CircleCollider* other, Point& p);
		virtual bool CheckCollisionRect(RectCollider* other, Point& p);

		virtual Vector GetSurfaceNormal(const Point& p);

		//Point GetCentre();
		//void SetCentre(Point centre);

		virtual void GetDimensions(float (&dimensions)[COORDNUM]) const;
		//dimensions (radius) is set to be first dimension given
		virtual void SetDimensions(float dimensions[COORDNUM]);

		float GetRadius();
		void SetRadius(float radius);

	private:
		//Point m_centre; from base class
		float m_radius;
};
#endif
