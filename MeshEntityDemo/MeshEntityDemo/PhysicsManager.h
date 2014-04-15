#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#define PI 3.14159265359

#include "..\..\Engine\Advanced2D.h"

const D3DXVECTOR3 ZERO_VECTOR(0, 0, 0);

class PhysicsManager
{
public:
	bool scoring[2];
	PhysicsManager(void);
	~PhysicsManager(void);

	void Update();

	void AddPhysicsBody(Advanced2D::Mesh* body);
	
	bool AwardPlayerOnePoints() 
	{ 
		return scoring[0]; 
		scoring[1] = false;
	}
	bool AwardPlayerTwoPoints() 
	{ 
		return scoring[1];
		scoring[1] = false;
	}

private:
	void CheckCollisionPair (Advanced2D::Mesh* mesh1, Advanced2D::Mesh* mesh2);
	void HandleCollision();
	// runs through all the physics bodies in the scene, and calls HandleCollision between any two bodies that could collide
	void CheckForCollisions();
	// checks if the two bodies are colliding, and applies forces if they are
	void HandleCollision(Advanced2D::Mesh* object1, Advanced2D::Mesh* object2);
	// applies innate forces, such as friction and gravity
	void UpdateVelocity();
	void UpdatePosition();
	
	// given a vector3, returned a normalized vector
	D3DXVECTOR3 Normalize (D3DXVECTOR3);
	// calculate length of a vector3
	float DXVectorLength (D3DXVECTOR3);
	// calculate dot product of 2 vectors
	float DXVectorDotProduct (D3DXVECTOR3 vec1, D3DXVECTOR3 vec2);

	// list of physics bodies in the scene
	std::list<Advanced2D::Mesh*> physicsBodies;

	// physics clock variables
	clock_t currTime, prevTime;
	float dt;

	// physics variables
	float frictionAcceleration;
};

#endif

