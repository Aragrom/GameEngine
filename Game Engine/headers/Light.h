#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
using glm::vec4;
using glm::vec3;

#include "Component.h"

class Light :public Component
{
public:

	Light();	// Constructor
	~Light();	// Deconstructor

	// Getters
	vec4& getDiffuseColour();
	vec4& getSpecularColour();
	vec3& getDirection();

	// Setters
	void setDiffuseColour(float r, float g, float b, float a);
	void setSpecularColour(float r, float g, float b, float a);
	void setDirection(float x, float y, float z);

	void update();

private:

	float m_fAngle;										// Current rotation
	float m_fSinX;										// Value for Rotating
	float m_fCosZ;										// Value for Rotating

	// Light Properties
	vec4 m_DiffuseColour;		// Base colour
	vec4 m_SpecularColour;		// Highlight colour
	vec3 m_LightDirection;		// Direction of light (Theory: Infinite distance - 'Sun')
	bool m_bGettingBrighter;	// Used for alternating the updating of the light direction
};

#endif