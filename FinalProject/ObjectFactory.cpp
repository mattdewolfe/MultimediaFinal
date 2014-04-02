#include "ObjectFactory.h"
#define TILESIZE 64

ObjectFactory::ObjectFactory(int _startSize) : totalObjects (0)
{
	// Create object array with new max and allocate memory
	objects.reserve(_startSize);
}
void ObjectFactory::AddObject(Advanced2D::Entity* _newObject)
{
	// If total objects has reached negative value, reset to 0 (debug line as this should not happen)
	if (totalObjects == -1)
		totalObjects = 0;
	// Add object to highest position, then increment total objects
	if (_newObject)
	{
		objects.push_back(_newObject);
		totalObjects++;
	}
}
void ObjectFactory::DrawAll()
{	
	for (int i = 0; i < totalObjects; i++)
	{
		// draw call
	}
}
#pragma region DestroyFunctions
bool ObjectFactory::Destroy(Advanced2D::Entity* target)
{
	// Iterate through and find matching object
	for (int i = 0; i < totalObjects; i++)
	{
		// When match is found call Destroy with index
		if (objects[i] == target)
			return DestroyAtIndex(i);
	}
	// Returns false if target was not found
	return false;
}

bool ObjectFactory::Destroy(float _targetX, float _targetY, float targetZ)
{
	// Iterate through and find matching object
	for (int i = 0; i < totalObjects; i++)
	{
	}
	// Returns false if target was not found
	return false;
}

bool ObjectFactory::DestroyAtIndex(int _index)
{
	// Ensure index requested is within bounds of exisiting objects
	if (_index > totalObjects || totalObjects <= 0)
		return false;

	// Swap given index with last object in array, and decrement array size
	objects[_index] = objects[totalObjects - 1];
	objects.pop_back();
	totalObjects--;
	return true;
}
#pragma endregion DestroyFunctions
void ObjectFactory::Clear()
{
	objects.clear();
	totalObjects = 0;
}
void ObjectFactory::SetupLevel()
{
}

// MD