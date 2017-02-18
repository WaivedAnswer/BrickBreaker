//DeathWall.cpp
#include "DeathWall.h"
#include "Ball.h"
#include "Player.h"
#include "ReadyState.h"
#include "PlayState.h"
#include <iostream>
DeathWall::DeathWall() :
Wall()
{
    //calls default constructor for wall
}

DeathWall::DeathWall(float hwidth, float hheight, float x, float y) :
Wall(hwidth, hheight, x, y)
{
    //calls wall normal constructor
}

DeathWall::~DeathWall()
{
}

void DeathWall::InteractBall(Ball* ball)
{
	Player* player = ball->GetPlayer();
	if(player == nullptr)
	{
		return;
	}
	player->SetLives(player->GetLives() - 1);
	PlayState::Instance()->ResetStartPositions();

}
