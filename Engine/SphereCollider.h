#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "Collider.h"
class SphereCollider : public Collider
{
public:
	SphereCollider(float radius);
	~SphereCollider(void);
	float GetRadius() { return m_radius; }
private:
	float m_radius;
	
	// need to provide support for rotation, figure out quaternions
};
#endif

