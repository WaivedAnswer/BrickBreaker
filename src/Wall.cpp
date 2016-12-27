//Wall.cpp
#include "Wall.h"
#include "common.h"
#include "commonSDL.h"
#include "ObjectVisitor.h"
#include "RectCollider.h"
#include "CircleCollider.h"

Wall::Wall()
{
	m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0),GRID_RATIO, GRID_RATIO/10.0), Vector(0.0,0.0), Point((m_dimensions[0])/2.0, m_dimensions[1]/2.0), false);
	m_dimensions[0] = GRID_RATIO;
	m_dimensions[1] = GRID_RATIO/10.0;
	m_position[0] = 0.0;
	m_position[1] = 0.0;
}

Wall::Wall(float hwidth, float hheight, float x, float y)
{
	m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0), hwidth, hheight), Vector(0.0,0.0), Point(x, y), false);

	/*m_dimensions[0] = width;
	m_dimensions[1] = height;
	m_position[0] = x;
	m_position[1] = y;*/
}

Wall::~Wall() 
{
}


void Wall::Update(World* world, double lastClock)
{
	if(world == nullptr)
	{
		return;
	}
	//nothing to update currently
	for(std::list<GameObject*>::iterator it = world->GetObjectsBegin(); it != world->GetObjectsEnd(); ++it)
	{
		Point intersect;
		if(this->CheckCollision(*it, intersect))
		{
			m_body->HandleCollision((*it)->GetPhysicsBody(), intersect);
			(*it)->InteractWall(this);
		}
	}
}

void Wall::Draw()
{
	float dimensions[COORDNUM];
	m_body->GetDimensions(dimensions);
	Point centre = m_body->GetPosition();
	SDL_Rect fillRect = { 
	static_cast<int>(SCREEN_WIDTH / GRID_RATIO * (centre[0] -dimensions[0])),
  	static_cast<int>(SCREEN_HEIGHT / GRID_RATIO * (centre[1] -dimensions[1])),  	
	static_cast<int>(SCREEN_WIDTH / GRID_RATIO * 2*dimensions[0]),  		
	static_cast<int>(SCREEN_HEIGHT / GRID_RATIO * 2*dimensions[1]) };

	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
	SDL_RenderFillRect( gRenderer, &fillRect );
}
bool Wall::CheckCollision(GameObject* other, Point& p)
{
	//do nothing, walls don't need to check themselves for collisions currently, that is on the other objects that interact with them
	return false;
}

void Wall::Interact(ObjectVisitor* visitor)
{
	visitor->InteractWall(this);
}

void Wall::Interact(GameObject* other)
{
	other->InteractWall(this);
}

void Wall::InteractBall(Ball* ball)
{
}

