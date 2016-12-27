//Collider.h
#ifndef _COLLIDER_H
#define _COLLIDER_H
#include "common.h"

class CircleCollider;
class RectCollider;

class Collider
{
	public:
		Collider() {};
		virtual ~Collider() {};
		//the generic collision call
		virtual bool CheckCollision(Collider* other, Point& p) = 0;
		//specific collision calls
		virtual bool CheckCollisionCircle(CircleCollider* other, Point& p) = 0;
		virtual bool CheckCollisionRect(RectCollider* other, Point& p) = 0;

		virtual Vector GetSurfaceNormal(const Point& p) = 0;

		virtual void GetDimensions(float (&dimensions)[COORDNUM]) const = 0;
		virtual void SetDimensions(float dimensions[COORDNUM]) = 0;

		Point GetCentre() const { return m_centre;};
		void SetCentre(Point position) {m_centre = position;};
	protected:
		Point m_centre;
};
#endif

