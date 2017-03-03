//Brick.cpp
#include "Brick.h"
#include "commonSDL.h"
#include "ObjectVisitor.h"
#include "RectCollider.h"
#include "Player.h"
#include <algorithm>

Brick::Brick()
{
}

Brick::~Brick()
{
    
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

