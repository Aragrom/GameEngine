#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameConstants.h"

// Base class for colliders
class Collider : public Component
{
public:

	//Setters
	void setColliderType(std::string strType) { m_ColliderType = strType; }		// Collider type Can be 'SphereCollider' or 'BoxCollider'
	void setOffSet(vec3 v3) { m_v3OffSet = v3; }								// For offsetting collider from gameObjects transform position

	//Getters
	std::string getColliderType() { return m_ColliderType; }
	vec3 getOffSet() { return m_v3OffSet; }

	Collider();		// Constructor
	~Collider();	// Deconstructor

private:

	vec3 m_v3OffSet;			// Vec3 holding the colliders offset
	std::string m_ColliderType;	// String representing Collider type
};

#endif

