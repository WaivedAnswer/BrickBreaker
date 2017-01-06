//Actor.cpp
#include "Actor.h"
#include "common.h"
#include "commonSDL.h"
#include <cmath>
#include <iostream>
#include "ObjectVisitor.h"
#include "RectCollider.h"
#include "Collider.h"
#include "CircleCollider.h"

Actor::Actor()
{
	m_canMove = true;
	m_dimensions[0] = 6.0;
	m_dimensions[1] = 2.5;
	m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0), m_dimensions[0], m_dimensions[1]), Vector(0.0,0.0), Point((GRID_RATIO - m_dimensions[0])/2.0, GRID_RATIO*0.85), false);
	m_speed = DEFAULT_ACTOR_SPEED;
	/*m_dimensions[0] = 10.0;
	m_dimensions[1] = 5.0;
	m_position[0] = static_cast<float>(GRID_RATIO)/2.0 - m_dimensions[0]/2.0;
	m_position[1] = static_cast<float>(GRID_RATIO) - m_dimensions[1];
	m_speed = 2.0;
	m_direction = NONE;*/
}
Actor::Actor(float dimensions[2], float position[2], bool canMove, float speed)
{
	/*m_canMove = canMove;
	m_dimensions[0] = dimensions[0];
	m_dimensions[1] = dimensions[1];
	m_position[0] = position[0];
	m_position[1] = position[1];
	m_speed = speed;
	m_direction = NONE;*/
}

Actor::Actor(PhysicsBody* body, bool canMove)
{
	m_body = body;
	m_canMove = canMove;
}

Actor::~Actor()
{
	/*if(m_body != nullptr)
	{
		delete m_body;
		m_body = nullptr;
	}*/
}

void Actor::Update(World* world, double lastClock)
{
	if(world == nullptr)
	{
		return;
	}

	this->Move(lastClock);

	for(std::list<GameObject*>::iterator it = world->GetObjectsBegin(); it != world->GetObjectsEnd(); ++it)
	{
		Point intersect;
		if(this->CheckCollision(*it, intersect))
		{
			this->UnMove(lastClock);
			m_body->HandleCollision((*it)->GetPhysicsBody(), intersect);
			(*it)->InteractActor(this);
		}
	}
}

void Actor::Draw()
{
	//Render red filled quad
	float dimensions[COORDNUM];
	m_body->GetDimensions(dimensions);
	Point centre = m_body->GetPosition();
	SDL_Rect fillRect = { 
	static_cast<int>(SCREEN_WIDTH / GRID_RATIO * (centre[0] -dimensions[0])),
  	static_cast<int>(SCREEN_HEIGHT / GRID_RATIO * (centre[1] -dimensions[1])),  	
	static_cast<int>(SCREEN_WIDTH / GRID_RATIO * 2*dimensions[0]),  		
	static_cast<int>(SCREEN_HEIGHT / GRID_RATIO * 2*dimensions[1]) };

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( gRenderer, &fillRect );
}

bool Actor::CheckCollision(GameObject* other, Point& p)
{
	/*//TODO look into a more graceful version of this
	float* otherDim = other->GetDimensions();
	float* otherPos = other->GetPosition();
	float mleft = m_position[0];
	float mright = m_position[0] + m_dimensions[0];
	float mtop = m_position[1];
	float mbot = m_position[1] + m_dimensions[1];
	float oleft = otherPos[0];
	float oright = otherPos[0] + otherDim[0];
	float otop = otherPos[1];
	float obot = otherPos[1] + otherDim[1];

	bool leftOverlap = mleft < oright && mleft > oleft;
	bool rightOverlap = mright > oleft && mright < oright;
	bool topOverlap = mtop < obot && mtop > otop;
	bool botOverlap = mbot > otop && mbot < obot;

	if((leftOverlap || rightOverlap) && (topOverlap || botOverlap))
	{
		std::cout << leftOverlap << rightOverlap << topOverlap << botOverlap;
		return true;
	}

	return false;*/
	if(other == nullptr || other == this)
	{
		return false;
	}
	return m_body->CheckCollision(other->GetPhysicsBody(), p);
}



void Actor::Interact(ObjectVisitor* visitor)
{
	visitor->InteractActor(this);
}

void Actor::Interact(GameObject* other)
{
	other->InteractActor(this);
}

void Actor::InteractBall(Ball* other)
{
	other->SetPlayer(m_player);
	PhysicsBody* oBody = other->GetPhysicsBody();
	if(oBody == nullptr || m_body == nullptr)
	{
		return;
	}
	
	Vector diff = oBody->GetPosition() - m_body->GetPosition();
	Vector bVel = oBody->GetVelocity();

	float speed = sqrt(Dot(bVel, bVel));
	/*float left = sqrt(Dot(diff, normal::LEFT));
	float right = sqrt(Dot(diff, normal::RIGHT));
	
	if(left > 0)
	{
		diff = bVel.Normalize() + 0.6*left * normal::LEFT;
	}
	else if(right > 0)
	{
		diff = bVel.Normalize() + 0.6*right * normal::RIGHT;
	}
	else
	{
		diff = bVel;
	}*/
	diff = bVel.Normalize() + 0.6*diff.Normalize();
	diff.Normalize();
	//std::cout << diff;
	//std::cout << diff.Normalize();
	oBody->SetVelocity(speed * diff);
	//std::cout << oBody->GetVelocity() << "\n";
	//TODO implement later
}

void Actor::SetDirection(Directions direction)
{
	switch(direction)
	{
		case LEFT:
			m_body->SetVelocity(m_speed*normal::LEFT);
			break;
		case RIGHT:
			m_body->SetVelocity(m_speed*normal::RIGHT);
			break;
		case UP:
			//m_position[1] -= m_speed;
			break;	
		case DOWN:
			//m_position[1] += m_speed;
			break;
		case NONE:
			m_body->SetVelocity(normal::NONE);
			break;
	}
}
//add world reference
void Actor::Move(double lastClock)
{
	if(!m_canMove || m_body == nullptr)
	{
		return;
	}
	//TODO update time to work more effectively
	m_body->Move(GetTime(lastClock));
	/*switch(m_direction)
	{
		case LEFT:
			m_position[0] -= m_speed;
			break;
		case RIGHT:
			m_position[0] += m_speed;
			break;
		case UP:
			m_position[1] -= m_speed;
			break;	
		case DOWN:
			m_position[1] += m_speed;
			break;
	}*/
}

void Actor::UnMove(double lastClock)
{
	if(!m_canMove || m_body == nullptr)
	{
		return;
	}
	m_body->UnMove(GetTime(lastClock));
	/*switch(m_direction)
	{
		case LEFT:
			m_position[0] += m_speed;
			break;
		case RIGHT:
			m_position[0] -= m_speed;
			break;
		case UP:
			m_position[1] += m_speed;
			break;	
		case DOWN:
			m_position[1] -= m_speed;
			break;
	}*/
}

void Actor::SetCanMove(bool canMove)
{
	m_canMove = canMove;
}

Player* Actor::GetPlayer()
{
	return m_player;
}

void Actor::SetPlayer(Player* player)
{
	m_player = player;
}
