//StandardWall.cpp
#include "StandardWall.h"

StandardWall::StandardWall() :
Wall()
{
	/*m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0),GRID_RATIO, GRID_RATIO/10.0), Vector(0.0,0.0), Point((m_dimensions[0])/2.0, m_dimensions[1]/2.0), false);
	m_dimensions[0] = GRID_RATIO;
	m_dimensions[1] = GRID_RATIO/10.0;
	m_position[0] = 0.0;
	m_position[1] = 0.0;*/
}

StandardWall::StandardWall(float hwidth, float hheight, float x, float y) :
Wall(hwidth, hheight, x, y)
{
	/*m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0), hwidth, hheight), Vector(0.0,0.0), Point(x, y), false);*/

	/*m_dimensions[0] = width;
	m_dimensions[1] = height;
	m_position[0] = x;
	m_position[1] = y;*/
}

StandardWall::~StandardWall()
{
}

void StandardWall::InteractBall(Ball* ball)
{
	//do nothing
}
