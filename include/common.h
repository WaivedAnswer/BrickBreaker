//common.h
#ifndef _COMMON_H
#define _COMMON_H
//non SDL related
#include <iostream>

class World;

extern World* WORLD;

const int COORDNUM = 2;

const float DEFAULT_BALL_SPEED = 0.1;
const float DEFAULT_ACTOR_SPEED = 0.1;

enum Directions
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};


struct Vector
{
	Vector() : x(0), y(0) {};
	Vector(float vx, float vy) : x(vx), y(vy) {};
	float x = 0;
	float y = 0;

	Vector Normalize();

	float operator [](int index) const;

	friend std::ostream& operator <<(std::ostream& os, const Vector& v);

	Vector operator +(const Vector& other) const;

	Vector operator -(const Vector& other) const;

	Vector operator =(const Vector& other);

	bool operator ==(const Vector& other) const;
};

namespace normal
{
	const Vector UP(0,-1);
	const Vector DOWN(0, 1);
	const Vector LEFT(-1,0);
	const Vector RIGHT(1,0);
	const Vector NONE(0,0);
}

float Dot(const Vector& v1, const Vector& v2);

Vector operator*(const Vector& v, const float i);

Vector operator*(const float i, const Vector& v);

Vector operator/(const Vector& v, const float i);



struct Point
{
	Point() : x(0), y(0) {};
	Point(float px, float py) : x(px), y(py) {};

	float x = 0;
	float y = 0;
	
	float operator [](int index) const;
	
	float& operator [](int index);

	friend std::ostream& operator <<(std::ostream& os, const Point& p);

	Point operator +(const Vector& other) const;
	
	Point operator -(const Vector& other) const;
	
	Vector operator -(const Point& other) const;

	Point& operator =(const Point& other);

	bool operator ==(const Point& other) const;
};

//gets time between last time and current
double GetTime(double lastTime);

#endif
