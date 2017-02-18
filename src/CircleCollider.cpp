//CircleCollider.cpp
#include "CircleCollider.h"
#include <iostream>
#include "RectCollider.h"
CircleCollider::CircleCollider(Point centre, float radius)
{
	m_centre = centre;
	m_radius = radius;
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::CheckCollision(Collider* other, Point& p)
{
	if(other == nullptr)
	{
		return false;
	}
	return other->CheckCollisionCircle(this, p);
}

bool CircleCollider::CheckCollisionCircle(CircleCollider* other, Point& p)
{
	if(other == nullptr)
	{
		return false;
	}
	Vector dir = m_centre - other->GetCentre();

	//gets squared distance between centres
	float dist2 = Dot(dir,dir);
	
	float radiiSum = m_radius + other->GetRadius();
	bool collides = dist2 <= radiiSum * radiiSum;
	if(collides)
	{
		p = other->GetCentre() + other->GetRadius() * dir/dist2;
	}
	return collides;
}

bool CircleCollider::CheckCollisionRect(RectCollider* other, Point& p)
{
	if(other == nullptr)
	{
		return false;
	}
	float sqDist = SqDistPtToRect(m_centre, *other, p);
	return sqDist <= m_radius * m_radius;
}

Vector CircleCollider::GetSurfaceNormal(const Point &p)
{
	Vector normal = p - m_centre;
	return normal.Normalize();
}

/*Point CircleCollider::GetCentre()
{
	return m_centre;
}
void CircleCollider::SetCentre(Point centre)
{
	m_centre = centre;
}*/

void CircleCollider::GetDimensions(float (&dimensions)[COORDNUM]) const
{
	for(int i = 0; i < COORDNUM; i++)
	{
		dimensions[i] = m_radius;
	}
}

void CircleCollider::SetDimensions(float dimensions[COORDNUM])
{
	m_radius = dimensions[0];
}

float CircleCollider::GetRadius()
{
	return m_radius;
}
void CircleCollider::SetRadius(float radius)
{
	m_radius = radius;
}

