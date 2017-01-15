//World.cpp
#include "World.h"
#include "Actor.h"
#include "Ball.h"
#include "Brick.h"
#include "Wall.h"
#include "StandardWall.h"
#include "DeathWall.h"
#include "common.h"
#include "commonSDL.h"
#include <algorithm>
World::World()
{
}
World::~World()
{
	for(std::list<GameObject*>::iterator it = m_objList.begin(); it != m_objList.end(); ++it)
	{
		delete *it;
	}
	m_objList.clear();
}
void World::Update(double lastClock)
{
	for(std::list<GameObject*>::iterator it = m_objList.begin(); it != m_objList.end(); ++it)
	{
		(*it)->Update(this, lastClock);
	}
}
void World::Draw()
{
	for(std::list<GameObject*>::iterator it = m_objList.begin(); it != m_objList.end(); ++it)
	{
		(*it)->Draw();
	}
}

void World::Add(GameObject* object)
{
	if(object != nullptr)
	{
		m_objList.push_back(object);
	}
}

//also deletes memory of object
void World::Remove(GameObject* object)
{
	if(object == nullptr)
	{
		return;
	}
	std::list<GameObject*>::iterator it = std::find(m_objList.begin(), m_objList.end(), object);
	if(it != m_objList.end())
	{
		delete *it;
		//should remove duplicates as well if they exist
		m_objList.remove(object);
	}
	
}

void InitializeBrickList(std::list<GameObject*> &brickList)
{
	float minX = GRID_RATIO*0.2;
	float minY = GRID_RATIO*0.2;
	float maxX = GRID_RATIO*0.8;
	float maxY = GRID_RATIO*0.5;
	//make rows
	int colCount = 8;
	int rowCount = 5;
	float brickWidth = (maxX-minX)/static_cast<float>(colCount);
	float brickHeight = (maxY-minY)/static_cast<float>(rowCount);
	for (int i = 0; i<rowCount; i++)
	{
		for (int j=0; j<colCount; j++)
		{
			brickList.push_back(new Brick(brickWidth/2.0, brickHeight/2.0, minX + brickWidth*j, minY + brickHeight*i, 10));
		}
		
	}
}

void World::CreateWorld()
{
	//m_objList.push_back(new Actor());

	m_objList.push_back(new StandardWall(GRID_RATIO/2.0, GRID_RATIO/20.0, GRID_RATIO/2.0, 0.0));
	m_objList.push_back(new DeathWall(GRID_RATIO/2.0, GRID_RATIO/20.0, GRID_RATIO/2.0, GRID_RATIO+GRID_RATIO/20.0));
	m_objList.push_back(new StandardWall(GRID_RATIO/20.0, GRID_RATIO/2.0, 0.0, GRID_RATIO/2.0));
	m_objList.push_back(new StandardWall(GRID_RATIO/20.0, GRID_RATIO/2.0, GRID_RATIO, GRID_RATIO/2.0));

	InitializeBrickList(m_objList);
}

std::list<GameObject*>::iterator World::GetObjectsBegin()
{
	return m_objList.begin();
}
std::list<GameObject*>::iterator World::GetObjectsEnd()
{
	return m_objList.end();
}
