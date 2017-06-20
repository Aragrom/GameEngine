/*
==========================================================================
ParticleSystem.h
==========================================================================
*/

#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include "GL\glut.h"
#include "cShapes.h"
#include <vector>

class cStarfield : public cShapes
{
public:
	cStarfield();
	cStarfield(GLint theTextureID, glm::vec3 theFieldVolume);
	virtual void render(float rotAngle);
	virtual void initialise(cTexture theTexture);
	virtual void initialise(GLint theTextureID, glm::vec3 theFieldVolume);

private:

	GLfloat m_AliasedPointSizes[2];
	int m_NumStars;
	glm::vec3 m_FieldVolume;
	GLuint m_TextureID;
	glm::vec3 m_StarPos;
	std::vector<glm::vec3> m_StarField;

	void generateStarField();

};

#endif