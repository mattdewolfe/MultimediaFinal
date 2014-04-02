#ifndef OBJECT FACTORY_H
#define OBJECT_FACTORY_H

#include <vector>
#include "..\Engine\Advanced2D.h"

// aka WORLD ENGINE
class ObjectFactory
{
private:
	// Structure of all objects loaded into factory
	std::vector<Advanced2D::Entity*> objects;
	// Values for tracking total objects in array, and max objects allowed
	int totalObjects;

public:
	ObjectFactory(int _startSize = 25);
	// Get total size of object array
	int TotalObjectCount() { return totalObjects; }
	// Get object by index, used to loop through array
	Advanced2D::Entity* GetObject(int _index) 
	{
		if (_index < totalObjects)
			return objects[_index];
	}
	// Add an object to the array
	void AddObject(Advanced2D::Entity* _newObject);
	// Draw all visuals for objects in factory
	void DrawAll();
	// Logic performed on objects as needed
	void Update();
	// Remove target object from array based on the object
	bool Destroy(Advanced2D::Entity* target);
	// Remove an object based on x, y, and z position
	bool Destroy(float _x, float _y, float _z);
	// Load game objects in for a level (to be randomized)
	void SetupLevel();
	// Erases all objects in array
	void Clear();
	virtual ~ObjectFactory(void) {}

private:
	// Private destroy function, called within public destroy functions.
	// This swaps the index and last position object and then pops last
	bool DestroyAtIndex(int _index);
};

#endif
// MD