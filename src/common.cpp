#include "common.h"
#include <cmath>
#include <cassert>
#include <ctime>
Vector Vector::Normalize()
{
	float length = sqrt(Dot(*this,*this));
	//std::cout << *this << "\n";
	//std::cout << length << "\n";
	x = x/length;
	y = y/length;
	//std::cout << *this << "\n";
	return *this;
}

float Vector::operator [](int index) const
{
	switch(index)
	{
		case 0:
			return x;
		case 1:
			return y;
		default:
			return 0.0;
	}
}

std::ostream& operator <<(std::ostream& os, const Vector& v)
{
	os << "x: " << v.x << " y: " << v.y;
	return os;
}

Vector Vector::operator +(const Vector& other) const
{
	float newX = x + other.x;
	float newY = y + other.y;
	return Vector(newX, newY);
}

Vector Vector::operator -(const Vector& other) const
{
	float newX = x - other.x;
	float newY = y - other.y;
	return Vector(newX, newY);
}

Vector Vector::operator =(const Vector& other) 
{
	x = other.x;
	y = other.y;
	return *this;
}

bool Vector::operator ==(const Vector& other) const
{
	return (x == other.x) && (y == other.y);
}


float Dot(const Vector& v1, const Vector& v2)
{
	float sum = 0;
	for(int i = 0; i < COORDNUM; i++)
	{
		sum += v1[i]*v2[i];
	}

	return sum;
}

Vector operator*(const Vector& v, const float i)
{
	return Vector(v.x*i, v.y*i);
}

Vector operator*(const float i, const Vector& v)
{
	return v*i;
}

Vector operator/(const Vector& v, const float i)
{
	return v*(1.0/i);
}



float Point::operator [](int index) const
{
	assert(index >= 0 && index < 2);
	switch(index)
	{
		case 0:
			return x;
		case 1:
			return y;
	}
}

float& Point::operator [](int index)
{
	assert(index >= 0 && index < 2);
	switch(index)
	{
		case 0:
			return x;
		case 1:
			return y;
	}
}

std::ostream& operator <<(std::ostream& os, const Point& p)
{
	os << "x: " << p.x << " y: " << p.y;
	return os;
}

Point Point::operator +(const Vector& other) const
{
	float newX = x + other.x;
	float newY = y + other.y;
	return Point(newX, newY);
}

Point Point::operator -(const Vector& other) const
{
	float newX = x - other.x;
	float newY = y - other.y;
	return Point(newX, newY);
}

Vector Point::operator -(const Point& other) const
{
	float newX = x - other.x;
	float newY = y - other.y;
	return Vector(newX, newY);
}

Point& Point::operator =(const Point& other) 
{
	x = other.x;
	y = other.y;
	return *this;
}

bool Point::operator ==(const Point& other) const
{
	return (x == other.x) && (y == other.y);
}

double GetTime(double lastClock)
{
	clock_t curr = clock();
	return static_cast<double>(curr) - lastClock;
}

