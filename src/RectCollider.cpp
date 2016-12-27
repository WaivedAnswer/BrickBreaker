//RectCollider.cpp
#include "RectCollider.h"
#include "CircleCollider.h"
#include <iostream>
#include <algorithm>

RectCollider::RectCollider()
{
	m_centre = Point(0.0,0.0);
	m_dimensions[0] = 0.0;
	m_dimensions[1] = 0.0;
}

RectCollider::RectCollider(Point centre, float width, float height)
{
	m_centre = centre;
	m_dimensions[0] = width;
	m_dimensions[1] = height;
}

RectCollider::~RectCollider()
{
}

bool RectCollider::CheckCollision(Collider* other, Point& p)
{
	if(other == nullptr)
	{
		return false;
	}

	return other->CheckCollisionRect(this, p);
}

bool RectCollider::CheckCollisionCircle(CircleCollider* other, Point& p)
{
	//std::cout << "Rect to Circle\n";
	if(other == nullptr)
	{
		return false;
	}
	float sqDist = SqDistPtToRect(other->GetCentre(), *this, p);
	float radius = other->GetRadius();
	
	return sqDist <= radius*radius;
}

bool RectCollider::CheckCollisionRect(RectCollider* other, Point& p)
{
	//std::cout << "Rect to Rect\n";
	if(other == nullptr)
	{
		return false;
	}
	Point otherCentre = other->GetCentre();
	float otherDim[COORDNUM];
	other->GetDimensions(otherDim);
	for(int i = 0; i < COORDNUM; i++)
	{
		//mmin greater than omax
		if((m_centre[i] - m_dimensions[i]) > (otherCentre[i] + otherDim[i]))
		{
			return false;
		}
		//mmax less than omin
		else if((m_centre[i] + m_dimensions[i]) < (otherCentre[i] - otherDim[i]))
		{
			return false;
		}
	}
	return true;
}

Vector RectCollider::GetSurfaceNormal(const Point& p)
{
	Vector dir = p - m_centre;
	float up = Dot(dir, normal::UP)/m_dimensions[1];
	float down = Dot(dir, normal::DOWN)/m_dimensions[1];
	float left = Dot(dir, normal::LEFT)/m_dimensions[0];
	float right = Dot(dir, normal::RIGHT)/m_dimensions[0];
	//std::cout << up << down << left << right;
	float max = std::max({up,down,left,right});
	
	if(max == up)
	{
		return normal::UP;
	}

	else if(max == down)
	{
		return normal::DOWN;
	}

	else if(max == left)
	{
		return normal::LEFT;
	}
	//max must be right
	else 
	{
		return normal::RIGHT;
	}
}

/*Point RectCollider::GetCentre() const
{
	return m_centre;
}

void RectCollider::SetCentre(Point centre)
{
	m_centre = centre;
}*/

void RectCollider::GetDimensions(float (&dimensions)[COORDNUM]) const
{
	for(int i = 0 ; i < COORDNUM; i++)
	{
		dimensions[i] = m_dimensions[i];
	}
}

void RectCollider::SetDimensions(float dimensions[COORDNUM])
{
	for(int i = 0; i< COORDNUM; i++)
	{
		m_dimensions[i] = dimensions[i];
	}
}

float SqDistPtToRect(const Point& p, const RectCollider& collider, Point& intersect)
{
	float sqDist = 0.0;

	float dimensions[COORDNUM];
	collider.GetDimensions(dimensions);
	Point rectCentre = collider.GetCentre();

	float v = 0.0;
	float minR = 0.0;
	float maxR = 0.0;

	for(int i=0; i < COORDNUM; i++)
	{
		intersect[i] = v = p[i];
		
		minR = rectCentre[i] - dimensions[i];
		maxR = rectCentre[i] + dimensions[i]; 

		if(v < minR)
		{
			sqDist += (minR - v)*(minR - v);
			intersect[i] = minR;
		}
		else if (v > maxR)
		{
			sqDist += (v - maxR)*(v - maxR);
			intersect[i] = maxR;
		}
	}
	
	return sqDist;
}
