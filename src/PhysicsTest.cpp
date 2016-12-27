#include "PhysicsBody.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include <iostream>
//just necessary so that wall ball etc. don't complain
#include <SDL2/SDL.h>
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool MissingCircleColliderTest()
{
	CircleCollider * c1 = new CircleCollider(Point(0.0,0.0), 1.0);
	CircleCollider * c2 = new CircleCollider(Point(2.0,0.1), 1.0);
	Point p;
	bool collides1 = c1->CheckCollision(c2, p);
	bool collides2 = c2->CheckCollision(c1, p);
	delete c1;
	delete c2;
	return (collides1 == false) && (collides2 == false);
}

bool GrazingCircleColliderTest()
{
	CircleCollider * c1 = new CircleCollider(Point(0.0,0.0), 1.0);
	CircleCollider * c2 = new CircleCollider(Point(2.0,0.0), 1.0);
	Point p;
	bool collides1 = c1->CheckCollision(c2, p);
	bool collides2 = c2->CheckCollision(c1, p);
	delete c1;
	delete c2;
	return (collides1 == true) && (collides2 == true);
}

bool HittingCircleColliderTest()
{
	CircleCollider * c1 = new CircleCollider(Point(0.0,0.0), 1.0);
	CircleCollider * c2 = new CircleCollider(Point(1.0,0.0), 1.0);
	Point p;
	bool collides1 = c1->CheckCollision(c2, p);
	bool collides2 = c2->CheckCollision(c1, p);
	delete c1;
	delete c2;
	return (collides1 == true) && (collides2 == true);
}

void CircleTest()
{
	std::cout << "Circle Test, testing hit graze and miss of circle colliders\n";
	bool hit = HittingCircleColliderTest();
	bool graze = GrazingCircleColliderTest();
	bool miss = MissingCircleColliderTest();
	if ( hit && graze && miss)
	{
		std::cout << "CircleTest Succeeded\n";
	}
	else
	{
		std::cout << "CircleTest Failed \n" <<" Hit:" << hit << " Graze:" <<graze <<" Miss:" << miss << "\n";
	}
}

bool MissingRectColliderTest()
{
	RectCollider * c1 = new RectCollider(Point(0.0,0.0), 1.0, 1.0);
	RectCollider * c2 = new RectCollider(Point(2.01, 2.01), 1.0, 1.0);
	Point p;
	bool collides1 = c1->CheckCollision(c2, p);
	bool collides2 = c2->CheckCollision(c1, p);
	delete c1;
	delete c2;
	return (collides1 == false) && (collides2 == false);
}

bool GrazingRectColliderTest()
{
	RectCollider * c1 = new RectCollider(Point(0.0,0.0), 1.0, 1.0);
	RectCollider * c2 = new RectCollider(Point(2.0, 2.0), 1.0, 1.0);
	Point p;
	bool collides1 = c1->CheckCollision(c2, p);
	bool collides2 = c2->CheckCollision(c1, p);
	delete c1;
	delete c2;
	return (collides1 == true) && (collides2 == true);
}


bool HittingRectColliderTest()
{
	RectCollider * c1 = new RectCollider(Point(0.0,0.0), 1.0, 1.0);
	RectCollider * c2 = new RectCollider(Point(1.0, 1.0), 1.0, 1.0);
	Point p;
	bool collides1 = c1->CheckCollision(c2, p);
	bool collides2 = c2->CheckCollision(c1, p);
	delete c1;
	delete c2;
	return (collides1 == true) && (collides2 == true);
}



void RectTest()
{
	std::cout << "Rect Test, testing hit graze and miss of rect colliders\n";
	bool hit = HittingRectColliderTest();
	bool graze = GrazingRectColliderTest();
	bool miss = MissingRectColliderTest();
	if ( hit && graze && miss)
	{
		std::cout << "RectTest Succeeded\n";
	}
	else
	{
		std::cout << "RectTest Failed \n" <<" Hit:" << hit << " Graze:" <<graze <<" Miss:" << miss << "\n";
	}
}

bool HittingMixColliderTest()
{
	RectCollider * c1 = new RectCollider(Point(0.0,0.0), 1.0, 1.0);
	CircleCollider * c2 = new CircleCollider(Point(1.0, 1.0), 1.0);
	Point p;
	bool collides1 = c1->CheckCollision(c2, p);
	bool collides2 = c2->CheckCollision(c1, p);
	delete c1;
	delete c2;
	return (collides1 == true) && (collides2 == true);
}

bool GrazingMixColliderTest()
{
	RectCollider * c1 = new RectCollider(Point(0.0,0.0), 1.0, 1.0);
	CircleCollider * c2 = new CircleCollider(Point(2.0, 0.0), 1.0);
	Point p;
	bool collides1 = c1->CheckCollision(c2, p);
	bool collides2 = c2->CheckCollision(c1, p);
	delete c1;
	delete c2;
	return (collides1 == true) && (collides2 == true);
}

bool MissingMixColliderTest()
{
	RectCollider * c1 = new RectCollider(Point(0.0,0.0), 1.0, 1.0);
	CircleCollider * c2 = new CircleCollider(Point(2.0, 2.0), 1.0);
	Point p;
	bool collides1 = c1->CheckCollision(c2, p);
	bool collides2 = c2->CheckCollision(c1, p);
	delete c1;
	delete c2;
	return (collides1 == false) && (collides2 == false);
}


void RectCircleTest()
{
	std::cout << "Mix Test, testing hit graze and miss of rect and circle colliders\n";
	bool hit = HittingMixColliderTest();
	bool graze = GrazingMixColliderTest();
	bool miss = MissingMixColliderTest();
	if ( hit && graze && miss)
	{
		std::cout << "MixTest Succeeded\n";
	}
	else
	{
		std::cout << "RectTest Failed \n" <<" Hit:" << hit << " Graze:" <<graze <<" Miss:" << miss << "\n";
	}
}

void PhysicsBodyTest()
{
	std::cout << "Physics Body Test, testing hit graze and miss of rect and circle colliders, pre-movement and post-movement\n";
	PhysicsBody * b1 = new PhysicsBody(new RectCollider(Point(0.0,0.0), 1.0, 1.0), Vector(1.0,0.0), Point(0.0,0.0), true);
	PhysicsBody * b2 = new PhysicsBody(new CircleCollider(Point(3.0,0.0), 1.0), Vector(-1.0,0.0), Point(3.0,0.0), true);
	bool isCorrect = true;
	if(b1->HandleCollision(b2))
	{
		isCorrect = false;
		std::cout << "Incorrect Collision\n";
	}
	else
	{
		std::cout << "No collision b1 -> b2\n";
	}
	if(b2->HandleCollision(b1))
	{
		isCorrect = false;	
		std::cout << "Incorrect Collision\n";
	}
	else
	{
		std::cout << "No collision b2 -> b1\n";
	}

	b1->Move(1.0);
	b2->Move(1.0);
	
	if(!b1->HandleCollision(b2))
	{
		isCorrect = false;
		std::cout << "Incorrect no Collision\n";
	}
	else
	{
		std::cout << "Collision b1 -> b2\n";
	}
	if(!b2->HandleCollision(b1))
	{
		isCorrect = false;
		std::cout << "Incorrect no Collision\n";
	}
	else
	{
		std::cout << "Collision b1 -> b2\n";
	}
	if(isCorrect)
	{
		std::cout << "Body test succeeded.\n";
	}
	else
	{
		std::cout << "Body test failed.\n";	
	}
}

void SurfaceNormalTest()
{
	RectCollider * c1 = new RectCollider(Point(0.0,0.0), 10.0, 1.0);
	Point p1(10.0,0.5);
	Point p2(5.0,1.0);
	Point p3(-10.0,-0.9);
	Point p4(-6.5, -1.0);
	
	std::cout << "Point 1: " << p1 << " gives normal: " << c1->GetSurfaceNormal(p1) << "\n";
	std::cout << "Point 2: " << p2 << " gives normal: " << c1->GetSurfaceNormal(p2) << "\n";
	std::cout << "Point 3: " << p3 << " gives normal: " << c1->GetSurfaceNormal(p3) << "\n";
	std::cout << "Point 4: " << p4 << " gives normal: " << c1->GetSurfaceNormal(p4) << "\n";
	
	delete c1;
}

int main(int argc, char* args[])
{
	/*CircleTest();
	RectTest();
	RectCircleTest();
	PhysicsBodyTest();*/
	SurfaceNormalTest();
	return 0;
}
