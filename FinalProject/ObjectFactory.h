#ifndef OBJECT FACTORY_H
#define OBJECT_FACTORY_H

#include <list>
#include "..\Engine\Advanced2D.h"

#define ARRAY_GROWTH 10
// aka WORLD ENGINE
class ObjectFactory
{
private:
	// Structure of all objects loaded into factory
	std::list<Advanced2D::Entity> objects;
	// Values for tracking total objects in array, and max objects allowed
	int totalObjects, maxObjects;

public:
	ObjectFactory();
	// Get total size of object array
	int const TotalObjectCount() { return totalObjects; }
	// Get object by index, used to loop through array
	/*Advanced2D::Entity* GetObject(int _index) 
	{
		return objects[_index];
	}*/
	
	// Add an object to the array
	void AddObject(Advanced2D::Entity *_newObject);
	// Draw all visuals for objects in factory
	void DrawAll();
	// Logic performed on objects as needed
	void Update();
	// Remove target object from array
	bool Destroy(Advanced2D::Entity *target);
	// Erases all objects in array
	void Clear() { objects.clear(); }
	virtual ~ObjectFactory(void) {}
};

#endif
