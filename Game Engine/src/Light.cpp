#include "Light.h"
#include "GameObject.h"
#include <glm/glm.hpp>
#include <iostream>

// Getters
vec4& Light::getSpecularColour() { return m_SpecularColour; }
vec4& Light::getDiffuseColour() { return m_DiffuseColour; }
vec3& Light::getDirection() { return m_LightDirection; }

// Setters
void Light::setSpecularColour(float r, float g, float b, float a) { m_SpecularColour = vec4(r, g, b, a); }
void Light::setDiffuseColour(float r, float g, float b, float a) { m_DiffuseColour = vec4(r, g, b, a); }
void Light::setDirection(float x, float y, float z) { m_LightDirection = vec3(x, y, z); }

// Constructor
Light::Light()
{
	m_DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_LightDirection = vec3(1.0f, 1.0f, 1.0f);
	m_Type = "Light";
	m_bGettingBrighter = true;

	m_fAngle = 0.0f;
	m_fSinX = 0.0f;
	m_fCosZ = 0.0f;
}

// Deconstructor
Light::~Light()
{

}

void Light::update()
{
	//std::cout << "Light Updated" << std::endl;

	m_fAngle += 0.01f;
	m_fSinX = sin(m_fAngle);
	m_fCosZ = -cos(m_fAngle);

	m_LightDirection.x = m_fSinX;
	m_LightDirection.z = m_fCosZ;

	// Ping Pong style lighting
	/*if (m_bGettingBrighter)
	{
		if (m_LightDirection.x <= 2.0f)
		{
			m_LightDirection.x += 0.01f;
			m_LightDirection.z += 0.01f;
		}
		else m_bGettingBrighter = false;
	}
	else
	{
		if (m_LightDirection.x >= -2.0f)
		{
			m_LightDirection.x -= 0.01f;
			m_LightDirection.z -= 0.01f;
		}
		else m_bGettingBrighter = true;
	}*/
}
