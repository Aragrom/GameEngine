#ifndef SphereCollider_h
#define SphereCollider_h

#include "GameConstants.h"

class SphereCollider : public Collider
{
public:

	//Getters
	float getRadius();

	//Setters
	void setRadius(float fRadius);

	SphereCollider(float fRadius); //Constructor

	bool withinColliderCheckPointer(vec3 *pos);
	bool withinColliderCheck(vec3 pos);
	bool withinColliderCheck(SphereCollider sphereCollider);

private:

	float m_fRadius;
};
#endif

