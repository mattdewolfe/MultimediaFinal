#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(void)
{
	scoring[0] = false;
	scoring[1] = false;
	
	currTime = clock();
	prevTime = currTime;
	dt = 0;

	frictionAcceleration = 0.001;
}

void PhysicsManager::Update()
{
	// Maybe move this to GameManager or main if any other classes need a timer
	// game timer
	currTime = clock();
	dt = currTime - prevTime;
	dt /= CLOCKS_PER_SEC; // convert to seconds, maybe unneccesary?
	if (dt > 1)
		dt = 1;
	prevTime = currTime;

	CheckForCollisions();
	UpdateVelocity();
	UpdatePosition();
}

void PhysicsManager::UpdateVelocity()
{
	// friction
	std::list<Advanced2D::Mesh*>::iterator physicsBodyIter;
	physicsBodyIter = physicsBodies.begin();

	while (physicsBodyIter != physicsBodies.end() )
	{
		Advanced2D::Mesh* mesh = *physicsBodyIter;
		if (mesh->getAwake() )
		{
			// apply friction
			if (DXVectorLength(mesh->GetVelocity() ) < 0.0001)
			{
				mesh->SetVelocity(ZERO_VECTOR);
			}
			else
			{
				D3DXVECTOR3 frictionVec = Normalize(mesh->GetVelocity());
				frictionVec.x *= (frictionAcceleration * dt * -1);
				frictionVec.y *= (frictionAcceleration * dt * -1);
				frictionVec.z *= (frictionAcceleration * dt * -1);

				mesh->SetVelocity(mesh->GetVelocity() + frictionVec);
			}
		}

		physicsBodyIter++;
	}
}

void PhysicsManager::UpdatePosition()
{
}

// this runs through the entire list of objects in physicsObject list, calls CheckCollisionPair to see of theyre colliding
void PhysicsManager::CheckForCollisions()
{
	std::list<Advanced2D::Mesh*>::iterator entityIter1;
	std::list<Advanced2D::Mesh*>::iterator entityIter2;
	Advanced2D::Mesh* mesh1;
	Advanced2D::Mesh* mesh2;

	entityIter1 = physicsBodies.begin();

	while (entityIter1 != physicsBodies.end() )
	{
		mesh1 = *entityIter1;

		if (mesh1->HasCollider() && mesh1->getAwake())			
		{
			entityIter2 = entityIter1;
			entityIter2++;

			while (entityIter2 != physicsBodies.end() )
			{
				mesh2 = *entityIter2;
				if (mesh2->HasCollider() && mesh2->getAwake() )
				{
					CheckCollisionPair(mesh1, mesh2);
				}
				entityIter2++;
			}
		}
		entityIter1++;
	}
}

void PhysicsManager::CheckCollisionPair(Advanced2D::Mesh* mesh1, Advanced2D::Mesh* mesh2)
{
	// if the two meshes are spheres
	if (mesh1->GetCollider()->GetType() == Collider::SPHERE && mesh2->GetCollider()->GetType() == Collider::SPHERE)
	{
		// if the two spheres are colliding
		if ( DXVectorLength( (mesh1->GetPosition() - mesh2->GetPosition() )) < ( ((SphereCollider*)mesh1->GetCollider())->GetRadius() + ((SphereCollider*)mesh2->GetCollider())->GetRadius() ))
		{
			
			// bounce the two spheres off of eachother
			D3DXVECTOR3 collisionNormal = mesh2->GetPosition() - mesh1->GetPosition();
			collisionNormal = Normalize(collisionNormal);

			float dotProdNumerator = DXVectorDotProduct(mesh1->GetVelocity(), collisionNormal);
			float dotProdDenominator = DXVectorLength(mesh1->GetVelocity()) * DXVectorLength(collisionNormal);
			float collisionAngle = acos(dotProdNumerator/ dotProdDenominator);		

			// prevents illogical collisions (i.e. moving objects colliding with stationary objects behind them)
			if (collisionAngle <= PI/2)
			{
				
				D3DXVECTOR3 temp = mesh1->GetVelocity();			
				mesh1->SetVelocity(mesh2->GetVelocity());
				mesh2->SetVelocity(temp);
				//mesh1->SetVelocity(-0.01,0,0);
				//mesh2->SetVelocity(-0.01,0,0);
			}
		}
	}

	// same collision type as below, simply swap order in order for calculations to work
	else if (mesh1->GetCollider()->GetType() == Collider::AABB && mesh2->GetCollider()->GetType() == Collider::SPHERE)
	{
		Advanced2D::Mesh* temp = mesh1;
		mesh1 = mesh2;
		mesh2 = temp;
		delete temp;
	}
	else if (mesh1->GetCollider()->GetType() == Collider::SPHERE && mesh2->GetCollider()->GetType() == Collider::AABB)
	{
		// using method found at http://www.gamedev.net/topic/335465-is-this-the-simplest-sphere-aabb-collision-test/
		// Post by DekuTree64

		D3DXVECTOR3 boxToSphere = mesh1->GetPosition() - mesh2->GetPosition();
		D3DXVECTOR3 closestPointOnBox;	
		
		// X axis 
		if (boxToSphere.x < -((AABBCollider*)mesh2->GetCollider())->GetWidth()/2)
		{
			closestPointOnBox.x = -((AABBCollider*)mesh2->GetCollider())->GetWidth()/2;
		}
		else if (boxToSphere.x > ((AABBCollider*)mesh2->GetCollider())->GetWidth()/2)
		{
			closestPointOnBox.x = ((AABBCollider*)mesh2->GetCollider())->GetWidth()/2;
		}
		else
		{
			closestPointOnBox.x = boxToSphere.x;
		}
		// Y axis
		if (boxToSphere.y < -((AABBCollider*)mesh2->GetCollider())->GetHeight()/2)
		{
			closestPointOnBox.y = -((AABBCollider*)mesh2->GetCollider())->GetHeight()/2;
		}
		else if (boxToSphere.y > ((AABBCollider*)mesh2->GetCollider())->GetHeight()/2)
		{
			closestPointOnBox.y = ((AABBCollider*)mesh2->GetCollider())->GetHeight()/2;
		}
		else
		{
			closestPointOnBox.y = boxToSphere.y;
		}
		// Z axis
		if (boxToSphere.z < -((AABBCollider*)mesh2->GetCollider())->GetDepth()/2)
		{
			closestPointOnBox.z = -((AABBCollider*)mesh2->GetCollider())->GetDepth()/2;
		}
		else if (boxToSphere.z > ((AABBCollider*)mesh2->GetCollider())->GetDepth()/2)
		{
			closestPointOnBox.z = ((AABBCollider*)mesh2->GetCollider())->GetDepth()/2;
		}
		else
		{
			closestPointOnBox.z = boxToSphere.z;
		}

		D3DXVECTOR3 distance = boxToSphere - closestPointOnBox;

		// not sure why these are all squared, check math again
		// find out if the sphere and AABB are colliding
		if (distance.x*distance.x + distance.y*distance.y + distance.z*distance.z < ((SphereCollider*)mesh1->GetCollider())->GetRadius() )
		{
			// if the AABB is the "target", destroy the plane and score for the player
			if (mesh2->getName() == "target")
			{
				if (mesh1->getName() == "team1")
					scoring[0] = true;
				else
					scoring[1] = true;

				mesh1->setVisible(false);
				mesh1->setAwake(false);

			}
			// if not the target, bounce the sphere off the AABB
			else
			{
				D3DXVECTOR3 collisionNormal = mesh1->GetPosition() - closestPointOnBox;
				collisionNormal = Normalize(collisionNormal);

				float dotProdNumerator = DXVectorDotProduct(mesh1->GetVelocity(), collisionNormal);
				float dotProdDenominator = DXVectorLength(mesh1->GetVelocity()) * DXVectorLength(collisionNormal);
				float collisionAngle = acos(dotProdNumerator/ dotProdDenominator);		

				// prevents illogical collisions (i.e. moving objects colliding with stationary objects behind them)
				if (collisionAngle <= PI/2)
				{
					D3DXVECTOR3 reboundVector = mesh1->GetVelocity();
					if (abs(collisionNormal.x) > abs(collisionNormal.z))
					{
						reboundVector.x = -reboundVector.x;
					}				
					else
					{
						reboundVector.z = -reboundVector.z;
					}
					mesh1->SetVelocity(reboundVector);
					//mesh1->SetVelocity(0,1,0);
					// collision
				}
			}
		}
	}
}

// Adds an object to be tracked by the physics manager.
// NOTE: Any objects put into this list MUST have a collider on them.
void PhysicsManager::AddPhysicsBody (Advanced2D::Mesh* body)
{
	if (body->HasCollider() )
		physicsBodies.push_back(body);
}

// Should look into how to add these functionalities directly into the D3DXVECTOR3 class
D3DXVECTOR3 PhysicsManager::Normalize (D3DXVECTOR3 vec)
{
	float mag = DXVectorLength(vec);
	vec.x = vec.x/mag;
	vec.y = vec.y/mag;
	vec.z = vec.z/mag;
	return vec;
}

float PhysicsManager::DXVectorLength (D3DXVECTOR3 vec)
{
	float length = 0;
	length += (vec.x * vec.x);
	length += (vec.y * vec.y);
	length += (vec.z * vec.z);
	return sqrt(length);
}

float PhysicsManager::DXVectorDotProduct (D3DXVECTOR3 vec1, D3DXVECTOR3 vec2)
{
	return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}


PhysicsManager::~PhysicsManager(void)
{
}
