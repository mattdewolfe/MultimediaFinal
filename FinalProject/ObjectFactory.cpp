#include "ObjectFactory.h"

ObjectFactory::ObjectFactory() : totalObjects (0), maxObjects (20)
{}

void ObjectFactory::AddObject(Advanced2D::Entity *_newObject)
{
	objects.push_back(*_newObject);
}

void ObjectFactory::DrawAll()
{		
	for (int i = 0; i < totalObjects; i++)
	{
		//objects[i]->Draw();
	}
}

bool ObjectFactory::Destroy(Advanced2D::Entity *target)
{
/*	// Iterate through and find matching object
	for (int i = 0; i < totalObjects; i++)
	{
		// When match is found call destroyAndRepack with index
		if (objects[i] == target)
	}
	// Returns false if target was not found*/
	return false;
}