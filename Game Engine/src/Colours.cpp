#include "Colours.h"

Colours::Colours()
{
	setColourList();
}

glm::vec3 Colours::getColour(colours colour)
{
	return m_ColourList[colour];
}

void Colours::setColourList()
{
	m_ColourList[0] = glm::vec3(1.0f, 0.0f, 0.0f); //Red
	m_ColourList[1] = glm::vec3(1.0f, 1.0f, 0.0f); //Yellow
	m_ColourList[2] = glm::vec3(0.0f, 1.0f, 0.0f); //Green
	m_ColourList[3] = glm::vec3(0.0f, 0.0f, 1.0f); //Blue
	m_ColourList[4] = glm::vec3(1.0f, 0.0f, 1.0f); //Purple
	m_ColourList[5] = glm::vec3(1.0f, 1.0f, 1.0f); //White
	m_ColourList[6] = glm::vec3(0.5f, 0.5f, 0.5f); //Grey
}