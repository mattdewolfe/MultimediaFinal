#include "SphereCollider.h"


SphereCollider::SphereCollider(float radius) : Collider(SPHERE)
{
	m_radius = radius;
}


SphereCollider::~SphereCollider(void)
{
}
