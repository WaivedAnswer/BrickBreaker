//World.cpp
#include "World.h"
#include "Actor.h"
#include "Ball.h"
#include "Brick.h"
#include "UnbreakableBrick.h"
#include "StandardBrick.h"
#include "Wall.h"
#include "StandardWall.h"
#include "DeathWall.h"
#include "common.h"
#include "commonSDL.h"
#include "json.hpp"
#include <algorithm>
#include <fstream>
#include <typeinfo>
#include <map>

using json = nlohmann::json;

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

//used for default initialization
void InitializeBrickList(std::list<GameObject*> &brickList)
{
	float minX = GRID_RATIO*0.2;
	float minY = GRID_RATIO*0.2;
	float maxX = GRID_RATIO*0.8;
	float maxY = GRID_RATIO*0.5;
	//make rows
	int colCount = 5;
	int rowCount = 4;
	float brickWidth = (maxX-minX)/static_cast<float>(colCount);
	float brickHeight = (maxY-minY)/static_cast<float>(rowCount);
	for (int i = 0; i<rowCount; i++)
	{
		for (int j=0; j<colCount; j++)
		{
			brickList.push_back(new StandardBrick(brickWidth/2.0, brickHeight/2.0, minX + brickWidth*j, minY + brickHeight*i, 0));
		}
		
	}
}

void World::CreateWorld()
{
	//m_objList.push_back(new Actor());

	m_objList.push_back(new StandardWall(GRID_RATIO/2.0, GRID_RATIO/20.0, GRID_RATIO/2.0, 0.0));
	m_objList.push_back(new DeathWall(GRID_RATIO/2.0, GRID_RATIO/20.0, GRID_RATIO/2.0, GRID_RATIO));
	m_objList.push_back(new StandardWall(GRID_RATIO/20.0, GRID_RATIO/2.0, 0.0, GRID_RATIO/2.0));
	m_objList.push_back(new StandardWall(GRID_RATIO/20.0, GRID_RATIO/2.0, GRID_RATIO, GRID_RATIO/2.0));

	InitializeBrickList(m_objList);
}

bool GetJSonProperties(const json& j, int &tileHeight, int &tileWidth, json &data, std::map<int,std::string> &idMap)
{
    //try {
        tileHeight = j["height"];
        tileWidth = j["width"];
        //takes data from base layer
        data = (j["layers"].at(0))["data"];
        json tilesets = j["tilesets"];
        for(json::iterator it = tilesets.begin(); it != tilesets.end(); ++it)
        {
            std::cout <<(*it);
            assert((*it)["tilecount"].get<int>() == 1);
            idMap[(*it)["firstgid"]] = (*it)["name"];
            std::cout << (*it)["name"];
        }
        
        
   // } catch (std::domain_error e) {
    //    std::cerr << "Json File does not contain key\n";
   //     return false;
   // }
    return true;
}

void World::CreateWorld(std::string filename)
{
    std::ifstream input(filename);
    json j;
    input >> j;
    int tileHeight = 0,tileWidth = 0;
    float brickWidth = 0;
    float brickHeight = 0;
    float minX = GRID_RATIO*0.2;
    float minY = GRID_RATIO*0.2;
    float maxX = GRID_RATIO*0.8;
    float maxY = GRID_RATIO*0.5;
    json data;
    std::map<int,std::string> idMap;


    if(!GetJSonProperties(j, tileHeight, tileWidth, data,idMap))
    {
        CreateWorld();
        return;
    }
    
    if(tileWidth == 0 || tileHeight == 0 || data.size()<=0 ||idMap.size() <=0)
    {
        std::cout << data.size();
        std::cout << idMap.size();
        CreateWorld();
        return;
    }
    
    brickWidth = (maxX-minX)/static_cast<float>(tileWidth);
    brickHeight = (maxY-minY)/static_cast<float>(tileHeight);
    
    int count = 0;
    
    for(json::iterator it = data.begin(); it != data.end(); ++it)
    {
        if(idMap[*it] == "Brick")
        {
            Brick* brick = new StandardBrick(brickWidth/2.0, brickHeight/2.0, minX + brickWidth*(count%tileWidth), minY + brickHeight*static_cast<int>(count/tileWidth), 10);
            m_objList.push_back(brick);
        }
        else if(idMap[*it] == "Broken")
        {
            Brick* brokenBrick = new StandardBrick(brickWidth/2.0, brickHeight/2.0, minX + brickWidth*(count%tileWidth), minY + brickHeight*static_cast<int>(count/tileWidth), 10);
            brokenBrick->HitBrick();
            m_objList.push_back(brokenBrick);
        }
        else if(idMap[*it] == "UnBreakable")
        {
            Brick* unBreakableBrick = new UnBreakableBrick(brickWidth/2.0, brickHeight/2.0, minX + brickWidth*(count%tileWidth), minY + brickHeight*static_cast<int>(count/tileWidth));
            m_objList.push_back(unBreakableBrick);
        }
        count++;
    }
    /*for (int i = 0; i<tileHeight; i++)
    {
        for (int j=0; j<tileWidth; j++)
        {
            m_objList.push_back(new Brick(brickWidth/2.0, brickHeight/2.0, minX + brickWidth*j, minY + brickHeight*i, 10));
        }
        
    }*/
    
    m_objList.push_back(new StandardWall(GRID_RATIO/2.0, GRID_RATIO/20.0, GRID_RATIO/2.0, 0.0));
    m_objList.push_back(new DeathWall(GRID_RATIO/2.0, GRID_RATIO/20.0, GRID_RATIO/2.0, GRID_RATIO));
    m_objList.push_back(new StandardWall(GRID_RATIO/20.0, GRID_RATIO/2.0, 0.0, GRID_RATIO/2.0));
    m_objList.push_back(new StandardWall(GRID_RATIO/20.0, GRID_RATIO/2.0, GRID_RATIO, GRID_RATIO/2.0));

}

std::list<GameObject*>::iterator World::GetObjectsBegin()
{
	return m_objList.begin();
}
std::list<GameObject*>::iterator World::GetObjectsEnd()
{
	return m_objList.end();
}
