/*
==========================================================================
Enemy.h
==========================================================================
*/

#ifndef _planet_h
#define _planet_h

#include "GameConstants.h"

class GameObject;

class Planet
{
public:

	//Setter
	void setGameObject(GameObject *go) { m_gameObject = go; }
	void setOrbitSpeed(float f) { m_fOrbitSpeed = f; }
	void setRotateState(bool b) { m_bRandomRotate = b; }
	void setOrbitState(bool b) { m_bOrbiting = b; }
	void setOrbitCenter(vec3 v3) { m_v3OrbitCenter = v3; }

	Planet(float fOrbitDistance);	// Constructor
	~Planet();						// Deconstructor

	void update();	
	void rotate();

private:

	GameObject *m_gameObject;
	vec3 m_v3OrbitCenter;
	bool m_bRandomRotate;
	bool m_bOrbiting;
	float m_fRotateX;
	float m_fRotateY;
	float m_fRotateZ;
	float m_fOrbitDistance;
	float m_fAngle;						// Current rotation
	float m_fSinX;						// Value for Rotating
	float m_fCosZ;						// Value for Rotating
	float m_fOrbitSpeed;
};

#endif
