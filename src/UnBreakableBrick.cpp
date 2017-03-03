//
//  UnBreakableBrick.cpp
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-03-02.
//  Copyright © 2017 Quinnter. All rights reserved.
//

#include "UnBreakableBrick.h"
#include "commonSDL.h"
#include "ObjectVisitor.h"
#include "RectCollider.h"
#include "Player.h"
#include <algorithm>

UnBreakableBrick::UnBreakableBrick()
{
    m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0), 5, 5), Vector(0.0,0.0), Point(0, 0), false);
    m_brick = new LTexture();
    int minScreenDim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(m_brick && !m_brick->loadFromFile("assets/brick.png"))
    {
        std::cerr << "Could not load brick texture.\n";
    }
    m_brick->setWidth(minScreenDim / GRID_RATIO * 5*2);
    m_brick->setHeight(minScreenDim / GRID_RATIO * 5*2);
    /*m_dimensions[0] = 10;
     m_dimensions[1] = 10;
     m_position[0] = 0;
     m_position[1] = 0;*/
    m_pointVal = 5;
    m_health = 2;
}
                                               
UnBreakableBrick::UnBreakableBrick(float hwidth, float hheight, float x, float y, int pointVal)
{
    m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0), hwidth, hheight), Vector(0.0,0.0), Point(x, y), false);
    m_brick = new LTexture();
    int minScreenDim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(m_brick && !m_brick->loadFromFile("assets/unbreakable.png"))
    {
        std::cerr << "Could not load brick texture.\n";
    }
    m_brick->setWidth(minScreenDim / GRID_RATIO * hwidth*2.0);
    m_brick->setHeight(minScreenDim / GRID_RATIO * hheight*2.0);
    
    m_pointVal = pointVal;
    m_health = INT_MAX;
    
}
UnBreakableBrick::~UnBreakableBrick()
{
    if(m_brick != nullptr)
    {
        delete m_brick;
        m_brick = nullptr;
    }
}

void UnBreakableBrick::Update(World* world, double lastClock)
{
    if(world == nullptr)
    {
        return;
    }
    
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

void UnBreakableBrick::Draw()
{
    float dimensions[COORDNUM];
    m_body->GetDimensions(dimensions);
    Point centre = m_body->GetPosition();
    int minScreenDim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //renders unbreakable

    if(m_brick != nullptr)
    {
        m_brick->render(minScreenDim / GRID_RATIO * (centre[0] -dimensions[0]), minScreenDim / GRID_RATIO * (centre[1] -dimensions[1]));
    }
    
}


void UnBreakableBrick::InteractBall(Ball* ball)
{
    //ball->InteractBrick(this);
    this->HitBrick();
    Player* ballPlayer = ball->GetPlayer();
    if(ballPlayer == nullptr)
    {
        return;
    }
    
    if(this->GetHealth() > 0)
    {
        ballPlayer->SetScore(ballPlayer->GetScore() + this->GetPointValue());
    }
    else
    {
        ballPlayer->SetScore(ballPlayer->GetScore() + 5.0 * this->GetPointValue());
    }
}

void UnBreakableBrick::HitBrick()
{
    //do nothing
}

int UnBreakableBrick::GetHealth()
{
    return m_health;
}

int UnBreakableBrick::GetPointValue()
{
    return m_pointVal;
}
