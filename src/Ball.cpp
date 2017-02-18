//Ball.cpp
#include "Ball.h"
#include "common.h"
#include "commonSDL.h"
#include <math.h>
#include <iostream>
#include "ObjectVisitor.h"
#include "CircleCollider.h"
#include "RectCollider.h"
#include "World.h"
#include <algorithm>

Ball::Ball()
{
	m_speed = DEFAULT_BALL_SPEED;
	m_angle = DEFAULT_BALL_ANGLE;
	m_dimensions[0] = 2.5;
	m_dimensions[1] = 2.5;
	m_body = m_body = new PhysicsBody(new CircleCollider(Point(0.0,0.0), m_dimensions[0]), m_speed * Vector(cos(m_angle),-sin(m_angle)), DEFAULT_BALL_POS, true);
	/*m_canMove = false;
	
	m_position[0] = static_cast<float>(GRID_RATIO)/2.0 - static_cast<float>(m_dimensions[0])/2.0;
	m_position[1] = static_cast<float>(GRID_RATIO) - m_dimensions[1]*5;*/
	m_player = nullptr;
	lastCollision = nullptr;
	m_canMove = true;
	m_ball = new LTexture();
	if(!m_ball->loadFromFile("assets/ball.png"))
	{
		std::cerr << "Could not load ball texture.\n";
	}
	int minScreenDim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_ball->setWidth(minScreenDim / GRID_RATIO * m_dimensions[0] * 2.0);
	m_ball->setHeight(minScreenDim / GRID_RATIO * m_dimensions[0] * 2.0);
}

//TODO shift this to work with defaults and physics body
Ball::Ball(float startSpeed, float startAngle)
{
	m_speed = startSpeed;
	m_angle = startAngle;
	m_canMove = false;
	m_dimensions[0] = 5.0;
	m_dimensions[1] = 5.0;
	m_position[0] = static_cast<float>(GRID_RATIO)/2.0 - static_cast<float>(m_dimensions[0])/2.0;
	m_position[1] = static_cast<float>(GRID_RATIO) - m_dimensions[1]*5;
	m_player = nullptr;
	lastCollision = nullptr;
	m_ball = new LTexture();
	if(!m_ball->loadFromFile("assets/ball.png"))
	{
		std::cerr << "Could not load ball texture.\n";
	}
}

Ball::~Ball()
{
	if(m_ball != nullptr)
	{
		delete m_ball;
		m_ball = nullptr;
	}
}

void Ball::Update(World* world, double lastClock)
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
			(*it)->InteractBall(this);
		}
	}
}

//TODO pull out drawing stuff later
void Ball::Draw()
{	
	//TODO switch to a circle instead of square
	float dimensions[COORDNUM];
	m_body->GetDimensions(dimensions);
	Point centre = m_body->GetPosition();
	int minScreenDim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_Rect fillRect = { 
	static_cast<int>(minScreenDim / GRID_RATIO * (centre[0] -dimensions[0])),
  	static_cast<int>(minScreenDim / GRID_RATIO * (centre[1] -dimensions[1])),  	
	static_cast<int>(minScreenDim / GRID_RATIO * 2*dimensions[0]),  		
	static_cast<int>(minScreenDim / GRID_RATIO * 2*dimensions[1]) };
	if(m_ball != nullptr)
	{
		m_ball->render(minScreenDim / GRID_RATIO *(centre[0] -dimensions[0]), minScreenDim / GRID_RATIO * (centre[1] -dimensions[1]));
	}
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0xFF );
	//SDL_RenderFillRect( gRenderer, &fillRect );
}

bool Ball::CheckCollision(GameObject* other, Point& p)
{

	if(other == nullptr || other == this || other == lastCollision )
	{
		return false;
	}
	if(m_body->CheckCollision(other->GetPhysicsBody(), p))
	{
		//lastCollision = other;
		return true;
	}
	
	return false;
}


void Ball::Interact(ObjectVisitor* visitor)
{
	visitor->InteractBall(this);
}

void Ball::Interact(GameObject* other)
{
	other->InteractBall(this);
}

//not sure if needed just now?
void Ball::InteractBrick(Brick* brick)
{
	brick->HitBrick();
	if(m_player == nullptr)
	{
		return;
	}

	if(brick->GetHealth() > 0)
	{
		m_player->SetScore(m_player->GetScore() + brick->GetPointValue());
	}
	else
	{
		m_player->SetScore(m_player->GetScore() + 5.0 * brick->GetPointValue());
	}
	/*if(brick->GetHealth() <= 0)
	{
		WORLD->Remove(brick);
	}*/
	//TODO implement later
}

void Ball::InteractActor(Actor* actor)
{
	this->SetPlayer(actor->GetPlayer());
	//TODO implement later
}

//moves the ball in the direction specified by angle and speed
void Ball::Move(double lastClock)
{
	if(!m_canMove || m_body == nullptr)
	{
		return;
	}

	m_body->Move(GetTime(lastClock));
	/*m_position[0] += m_speed*cos(m_angle);
	//as y is inverted
	m_position[1] -= m_speed*sin(m_angle);*/

}

//moves the ball back by the direction specified by angle and speed
void Ball::UnMove(double lastClock)
{
	if(!m_canMove || m_body == nullptr)
	{
		return;
	}
	m_body->UnMove(GetTime(lastClock));
	/*m_position[0] -= m_speed*cos(m_angle);
	//as y is inverted
	m_position[1] += m_speed*sin(m_angle);*/
}

void Ball::SetCanMove(bool canMove)
{
	m_canMove = canMove;
}

Player* Ball::GetPlayer()
{
	return m_player;
}

void Ball::SetPlayer(Player* player)
{
	m_player = player;
}

