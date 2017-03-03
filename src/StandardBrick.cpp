//
//  StandardBrick.cpp
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-03-02.
//  Copyright © 2017 Quinnter. All rights reserved.
//

#include "StandardBrick.h"
#include "commonSDL.h"
#include "ObjectVisitor.h"
#include "RectCollider.h"
#include "Player.h"
#include <algorithm>

StandardBrick::StandardBrick()
{
    m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0), 5, 5), Vector(0.0,0.0), Point(0, 0), false);
    m_brick = new LTexture();
    m_brokenBrick = new LTexture();
    int minScreenDim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(m_brick && !m_brick->loadFromFile("assets/brick.png"))
    {
        std::cerr << "Could not load brick texture.\n";
    }
    m_brick->setWidth(minScreenDim / GRID_RATIO * 5*2);
    m_brick->setHeight(minScreenDim / GRID_RATIO * 5*2);
    if(m_brokenBrick && !m_brokenBrick->loadFromFile("assets/brokenbrick.png"))
    {
        std::cerr << "Could not load broken brick texture.\n";
    }
    m_brokenBrick->setWidth(5*2);
    m_brokenBrick->setHeight(5*2);
    /*m_dimensions[0] = 10;
     m_dimensions[1] = 10;
     m_position[0] = 0;
     m_position[1] = 0;*/
    m_pointVal = 5;
    m_health = 2;
}

StandardBrick::StandardBrick(float hwidth, float hheight, float x, float y, int pointVal)
{
    m_body = new PhysicsBody(new RectCollider(Point(0.0,0.0), hwidth, hheight), Vector(0.0,0.0), Point(x, y), false);
    m_brick = new LTexture();
    m_brokenBrick = new LTexture();
    int minScreenDim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(m_brick && !m_brick->loadFromFile("assets/brick.png"))
    {
        std::cerr << "Could not load brick texture.\n";
    }
    m_brick->setWidth(minScreenDim / GRID_RATIO * hwidth*2.0);
    m_brick->setHeight(minScreenDim / GRID_RATIO * hheight*2.0);
    if(m_brokenBrick && !m_brokenBrick->loadFromFile("assets/brokenbrick.png"))
    {
        std::cerr << "Could not load broken brick texture.\n";
    }
    m_brokenBrick->setWidth(minScreenDim / GRID_RATIO * hwidth*2.0);
    m_brokenBrick->setHeight(minScreenDim / GRID_RATIO * hheight*2.0);
    /*m_dimensions[0] = width;
     m_dimensions[1] = height;
     m_position[0] = x;
     m_position[1] = y;*/
    m_pointVal = pointVal;
    m_health = 2;
    
}
StandardBrick::~StandardBrick()
{
    if(m_brick != nullptr)
    {
        delete m_brick;
        m_brick = nullptr;
    }
    if(m_brokenBrick != nullptr)
    {
        delete m_brokenBrick;
        m_brokenBrick = nullptr;
    }
}

void StandardBrick::Update(World* world, double lastClock)
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

void StandardBrick::Draw()
{
    float dimensions[COORDNUM];
    m_body->GetDimensions(dimensions);
    Point centre = m_body->GetPosition();
    int minScreenDim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //renders brick or broken brick image depending on health
    if(m_health >= 2)
    {
        if(m_brick != nullptr)
        {
            m_brick->render(minScreenDim / GRID_RATIO * (centre[0] -dimensions[0]), minScreenDim / GRID_RATIO * (centre[1] -dimensions[1]));
        }
    }
    else
    {
        if(m_brokenBrick != nullptr)
        {
            m_brokenBrick->render(minScreenDim / GRID_RATIO * (centre[0] -dimensions[0]), minScreenDim / GRID_RATIO * (centre[1] -dimensions[1]));
        }
    }
    
}


void StandardBrick::InteractBall(Ball* ball)
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
    /*if(m_health <= 0)
     {
     WORLD->Remove(this);
     }*/
    //TODO implement after
}

void StandardBrick::HitBrick()
{
    m_health--;
}

int StandardBrick::GetHealth()
{
    return m_health;
}
int StandardBrick::GetPointValue()
{
    return m_pointVal;
}
