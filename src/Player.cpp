//Player.cpp
#include "Player.h"
#include "Actor.h"
#include <algorithm>
Player::Player()
{
	m_score = 0;
	m_lives = 3;
	m_actor = nullptr;
	dirStack.push_back(NONE);
}

int Player::GetScore()
{
	return m_score;
}

void Player::SetScore(int score)
{
	m_score = score;
}

Actor* Player::GetActor()
{
	return m_actor;
}

void Player::SetActor(Actor* actor)
{
	//TODO might need to check if previous actor != nullptr delete?
	m_actor = actor;
	if(m_actor != nullptr)
	{
		m_actor->SetPlayer(this);
	}
}

int Player::GetLives()
{
	return m_lives;
}
	
void Player::SetLives(int lives)
{
	m_lives = lives;
}

//debate using commands here
void Player::HandleInput(SDL_Event& e)
{

	if(e.type == SDL_KEYUP)
	{
		switch( e.key.keysym.sym ) 
		{ 
			case SDLK_LEFT:
				dirStack.erase(std::remove(dirStack.begin(), dirStack.end(), LEFT), dirStack.end());
				if(!dirStack.empty())
				{
					m_actor->SetDirection(dirStack.back());
				}
				break;
			case SDLK_RIGHT:
				dirStack.erase(std::remove(dirStack.begin(), dirStack.end(), RIGHT), dirStack.end());
				if(!dirStack.empty())
				{
					m_actor->SetDirection(dirStack.back());
				}
				break;
			default:
				break;
		}
		//m_actor->SetDirection(NONE);
	}
	else if(e.type == SDL_KEYDOWN)
	{
		switch( e.key.keysym.sym ) 
		{ 
			case SDLK_LEFT:
				dirStack.push_back(LEFT);
				m_actor->SetDirection(LEFT);
				break;
			case SDLK_RIGHT:
				dirStack.push_back(RIGHT);
				m_actor->SetDirection(RIGHT);
				break;
			default:
				break;
		
		}
	}
	
}
