// Collider is an interface class
// Does not just contain collision info, but other physics properties such as mass (and maybe friction)
// would prefer to set up a component based system (similar to unitys) but not feasible at this time

#ifndef COLLIDER_H
#define COLLIDER_H
class Collider
{
// Variables
public:
	enum COLLIDER_TYPE {
		SPHERE, 
		AABB,
		PLANE,
		CYLINDER
	};

// Functions
public:
	
	//void SetType(TYPE type) { m_type = type; }
	COLLIDER_TYPE GetType() { return m_type; }
	void SetMass(float mass) { m_mass = mass; }
	float GetMass() { return m_mass; }
	virtual ~Collider(void) {};

protected:
	float m_mass;
	COLLIDER_TYPE m_type;
	Collider(COLLIDER_TYPE type) { m_type = type; };

private:
	// temp function, used to make this class an interface (to prevent instantiation of colliders with no type)
	//virtual void OverrideMe() = 0;
	
};
#endif

