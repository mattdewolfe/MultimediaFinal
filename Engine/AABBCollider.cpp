#include "AABBCollider.h"


AABBCollider::AABBCollider(float width, float height, float depth) : Collider(AABB)
{
	m_width = width;
	m_height = height;
	m_depth = depth;		
}


AABBCollider::~AABBCollider(void)
{
}
