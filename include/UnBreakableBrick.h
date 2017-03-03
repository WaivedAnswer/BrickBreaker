//
//  UnBreakableBrick.h
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-03-01.
//  Copyright © 2017 Quinnter. All rights reserved.
//

#ifndef UnBreakableBrick_h
#define UnBreakableBrick_h
#include "Brick.h"
class UnBreakableBrick : public Brick
{
public:
    UnBreakableBrick();
    UnBreakableBrick(float width, float height, float x, float y, int pointVal = 0);
    virtual ~UnBreakableBrick();
    
    virtual void Update(World* world, double lastClock);
    virtual void Draw();
    
    //inherited from Brick
    /*//should be stationary for the moment, don't need collision checking
    virtual bool CheckCollision(GameObject* other, Point& p);
    virtual void Interact(ObjectVisitor* visitor);
    virtual void Interact(GameObject* other);*/
    
    virtual void InteractBall(Ball* ball);
    
    virtual void HitBrick();
    virtual int GetHealth();
    virtual int GetPointValue();
    
private:
    //PhysicsBody* m_body; //inherited from base
    LTexture* m_brick;
    int m_pointVal;
    int m_health;
};

#endif /* UnBreakableBrick_h */
