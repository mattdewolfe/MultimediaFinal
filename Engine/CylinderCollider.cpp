#include "CylinderCollider.h"


CylinderCollider::CylinderCollider(float height, float radius) : Collider(CYLINDER)
{
	m_height = height;
	m_radius = radius;
}


CylinderCollider::~CylinderCollider(void)
{

}
