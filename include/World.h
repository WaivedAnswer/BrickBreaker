//World.h
#ifndef _WORLD_H
#define _WORLD_H
#include <list>
class GameObject;

class World
{
	public:
		World();
		~World();
		void Update(double lastClock);
		void Draw();
		void CreateWorld();
		void Add(GameObject* object);
		//also deletes memory of object
		void Remove(GameObject* object);
		//TODO figure out iterator pattern some other time
		std::list<GameObject*>::iterator GetObjectsBegin();
		std::list<GameObject*>::iterator GetObjectsEnd();
	private:
		std::list<GameObject*> m_objList;
		//save last frame time
};
#endif
