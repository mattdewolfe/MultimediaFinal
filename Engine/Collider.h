#ifndef COLLIDER_H
#define COLLIDER_H
class Collider
{
// Variables
public:
	enum TYPE {
		SPHERE, 
		AABB
	};
private:
	float mass;
	TYPE type;

// Functions
public:

	Collider();
	virtual ~Collider(void);
	void SetType(TYPE _type) { type = _type; }
	TYPE GetType() { return type; }
	void SetMass(float _mass) { mass = _mass; }
	float GetMass() { return mass; }

};
#endif

