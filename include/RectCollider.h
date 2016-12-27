//RectCollider.h
#ifndef _RECT_COLLIDER_H
#define _RECT_COLLIDER_H
#include "Collider.h"
#include "common.h"

class RectCollider : public Collider
{
	public:
		//halfwidth, halfheight
		RectCollider();
		RectCollider(Point centre, float hwidth, float hheight);
		virtual ~RectCollider();
		//generic collision call
		virtual bool CheckCollision(Collider* other, Point& p);

		//specific collision calls
		virtual bool CheckCollisionCircle(CircleCollider* other, Point& p);
		virtual bool CheckCollisionRect(RectCollider* other, Point& p);

		virtual Vector GetSurfaceNormal(const Point& p);

		//Point GetCentre() const;
		//void SetCentre(Point centre);
		virtual void GetDimensions(float (&dimensions)[COORDNUM]) const;
		virtual void SetDimensions(float dimensions[COORDNUM]);
	private:
		//Point m_centre; from base class
		//halfwidth halfheight
		float m_dimensions[COORDNUM];
};
//dist pt to rect, return
float SqDistPtToRect(const Point& p, const RectCollider& collider, Point& intersect);
#endif
