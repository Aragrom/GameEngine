/*
==================================================================================
ParticleSystem.cpp
==================================================================================
*/

#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{
	srand((unsigned)time(NULL));
	setRotAngle(0.0f);
	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, m_AliasedPointSizes);
	m_NumStars = 1000;
	m_TextureID = 0;
	m_FieldVolume = glm::vec3(1.0f,1.0f,1.0f);
	m_StarPos = glm::vec3(0.0f, 0.0f, 0.0f);

	generateStarField();
}

cStarfield::cStarfield(GLint theTextureID, glm::vec3 theFieldVolume)
{
	srand((unsigned)time(NULL));
	setRotAngle(0.0f);
	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, m_AliasedPointSizes);
	m_NumStars = 1000;
	m_TextureID = theTextureID;
	m_FieldVolume = theFieldVolume;
	m_StarPos = glm::vec3(0.0f, 0.0f, 0.0f);
	generateStarField();
}

void cStarfield::render(float rotAngle)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glEnable(GL_POINT_SPRITE);
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDepthMask(GL_FALSE);
	glPointSize(36.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 pointInSpace;
	glBegin(GL_POINTS);
	for (int loop = 0; loop < m_StarField.size(); loop++)
	{ 	
		pointInSpace = m_StarField.at(loop);
		glVertex3f(pointInSpace.x, pointInSpace.y, pointInSpace.z);
	}
	glEnd();

	glDisable(GL_POINT_SPRITE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void cStarfield::initialise(cTexture theTexture)
{
	srand((unsigned)time(NULL));
	glBindTexture(GL_TEXTURE_2D, theTexture.getTexture());
}

void cStarfield::initialise(GLint theTextureID, glm::vec3 theFieldVolume)
{
	srand((unsigned)time(NULL));
	m_TextureID = theTextureID;
	m_FieldVolume = theFieldVolume;

	glBindTexture(GL_TEXTURE_2D, m_TextureID);

}

void cStarfield::generateStarField()
{
	// generate starfield

	for (int loop = 0; loop < m_NumStars; loop++)
	{
		if (rand() % 3 == 0)
		{
			m_StarPos.x = -(rand() % (int)m_FieldVolume.x);
		}
		else
		{
			m_StarPos.x = (rand() % (int)m_FieldVolume.x);
		}
		if (rand() % 3 == 1)
		{
			m_StarPos.y = -(rand() % (int)m_FieldVolume.y);
		}
		else
		{
			m_StarPos.y = (rand() % (int)m_FieldVolume.y);
		}
		if (rand() % 3 == 2)
		{
			m_StarPos.z = -(rand() % (int)m_FieldVolume.z);
		}
		else
		{
			m_StarPos.z = (rand() % (int)m_FieldVolume.z);
		}
		m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, m_StarPos.z));
	}
}