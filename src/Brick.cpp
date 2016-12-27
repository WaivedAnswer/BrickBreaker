//Brick.cpp
#include "Brick.h"
#include "commonSDL.h"
#include "ObjectVisitor.h"
#include "RectCollider.h"
Brick::Brick()
{
	m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0), 5, 5), Vector(0.0,0.0), Point(0, 0), false);
	/*m_dimensions[0] = 10;
	m_dimensions[1] = 10;
	m_position[0] = 0;
	m_position[1] = 0;*/
	m_pointVal = 10;
	m_health = 2;
}
Brick::Brick(float hwidth, float hheight, float x, float y, int pointVal)
{
	m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0), hwidth, hheight), Vector(0.0,0.0), Point(x, y), false);
	/*m_dimensions[0] = width;
	m_dimensions[1] = height;
	m_position[0] = x;
	m_position[1] = y;*/
	m_pointVal = pointVal;
	m_health = 2;
	
}
Brick::~Brick()
{
}

void Brick::Update(World* world, double lastClock)
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
			(*it)->InteractBrick(this);
		}
	}
}

void Brick::Draw()
{
	//Render cyan filled quad 
	float dimensions[COORDNUM];
	m_body->GetDimensions(dimensions);
	Point centre = m_body->GetPosition();
	SDL_Rect fillRect = { 
	static_cast<int>(SCREEN_WIDTH / GRID_RATIO * (centre[0] -dimensions[0])),
  	static_cast<int>(SCREEN_HEIGHT / GRID_RATIO * (centre[1] -dimensions[1])),  	
	static_cast<int>(SCREEN_WIDTH / GRID_RATIO * 2*dimensions[0]),  		
	static_cast<int>(SCREEN_HEIGHT / GRID_RATIO * 2*dimensions[1]) };
	if(m_health > 2)
	{
		SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
	}
	else if(m_health > 1)
	{
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
	}
	else
	{
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
	}
	SDL_RenderFillRect( gRenderer, &fillRect );
}

bool Brick::CheckCollision(GameObject* other, Point& p)
{
	//do nothing as of yet.
	return false;
}


void Brick::Interact(ObjectVisitor* visitor)
{
	visitor->InteractBrick(this);
}

void Brick::Interact(GameObject* other)
{
	other->InteractBrick(this);
}

void Brick::InteractBall(Ball* ball)
{
	//ball->InteractBrick(this);
	this->HitBrick();
	/*if(m_health <= 0)
	{
		WORLD->Remove(this);
	}*/
	//TODO implement after
}

void Brick::HitBrick()
{
	m_health--;
}

int Brick::GetHealth()
{
	return m_health;
}
int Brick::GetPointValue()
{
	return m_pointVal;
}
