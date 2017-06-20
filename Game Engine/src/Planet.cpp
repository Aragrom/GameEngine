#include "Planet.h"

// Constructor
Planet::Planet(float fOrbitDistance) 
{
	m_fOrbitDistance = fOrbitDistance;
	m_fAngle = 0.0f;
	m_fSinX = 0.0f;
	m_fCosZ = 0.0f;
	m_fOrbitSpeed = 0.01f;
	m_bRandomRotate = false;
	m_bOrbiting = true;
	m_fRotateX = 0.5f;//(rand() % 10 + 1) / 100.0f;
	m_fRotateY = 0.01f;//(rand() % 10 + 1) / 100.0f;
	m_fRotateZ = 0.1f;//(rand() % 10 + 1) / 100.0f;
	m_v3OrbitCenter = vec3(0.0f, 0.0f, 0.0f);
}

// Deconstructor
Planet::~Planet() 
{

}

// SceneManager calls update on all planets
void Planet::update() 
{
	rotate();
}

void Planet::rotate() 
{
	// If planets is to orbit
	if (m_bOrbiting)
	{
		m_fAngle += m_fOrbitSpeed;		// increment angle using step
		m_fSinX = sin(m_fAngle);		// calculate new x value of rotation
		m_fCosZ = -cos(m_fAngle);		// calculate new z value of rotation

		//using orbitcenter (which does not change and set when instantiate in SceneManager) and sin() and -cos() values for the angle of x and z and set new position
		m_gameObject->getTransform()->setPosition(m_v3OrbitCenter.x + (m_fSinX * m_fOrbitDistance), m_v3OrbitCenter.y, m_v3OrbitCenter.z + (m_fCosZ * m_fOrbitDistance));
	}

	// if planet is to rotate - rotate based on a step size
	if (m_bRandomRotate)
	{
		vec3 v3CurRot = m_gameObject->getTransform()->getRotation();															// Get current ROTATION
		m_gameObject->getTransform()->setRotation(v3CurRot.x + m_fRotateX, v3CurRot.y + m_fRotateY, v3CurRot.z + m_fRotateZ);	// Set new ROTATION
	}
}