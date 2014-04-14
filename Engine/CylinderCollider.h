#ifndef CYLINDER_COLLIDER_H
#define CYLINDER_COLLIDER_H

#include "Collider.h"
class CylinderCollider : public Collider
{
public:
	CylinderCollider(float height, float radius);
	~CylinderCollider(void);
private:
	float m_height;
	float m_radius;
	
	// need to provide support for rotation, figure out quaternions
};
#endif

