//BrickRemover.cpp
#include "BrickRemover.h"
#include "common.h"
#include "GameObject.h"
#include "Brick.h"

BrickRemover::BrickRemover(World* world)
{
	m_world = world;
	m_brickCount = 0;
}

BrickRemover::~BrickRemover()
{
}


int BrickRemover::GetBrickCount()
{
	return m_brickCount;
}

void BrickRemover::RemoveBricks()
{
	if(m_world == nullptr)
	{
		return;
	}
	//Sets brick count to 0, as bricks interact with brick increments brickCount
	m_brickCount = 0;
	for(std::list<GameObject*>::iterator it = m_world->GetObjectsBegin(); it!= m_world->GetObjectsEnd(); ++it)
	{
		(*it)->Interact(this);
	}

	for(std::list<Brick*>::iterator it = m_removeList.begin(); it != m_removeList.end(); ++it)
	{
		m_world->Remove(*it); 
	}

	m_removeList.clear();

}

void BrickRemover::InteractBrick(Brick* brick)
{
	if(brick->GetHealth()<=0)
	{
		m_removeList.push_back(brick);
	}
	else
	{
		m_brickCount++;
	}
}
