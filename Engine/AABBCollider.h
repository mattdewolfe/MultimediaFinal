#ifndef AABB_COLLIDER_H
#define AABB_COLLIDER_H

#include "Collider.h"

class AABBCollider : public Collider
{
public:
	AABBCollider(float width, float height, float depth);
	~AABBCollider(void);
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
	float GetDepth() { return m_depth; }		
private:
	float m_width, m_height, m_depth;
	
	// need to provide support for rotation, figure out quaternions
};
#endif