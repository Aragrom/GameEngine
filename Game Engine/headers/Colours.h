#ifndef _COLOUR_H
#define _COLOUR_H

#include "glm\glm.hpp"

class Colours
{
public:

	enum colours
	{
		RED, YELLOW, GREEN, BLUE, PURPLE, WHITE, GREY
	};

	// Getter
	glm::vec3 getColour(colours colour);

	// Setter
	void setColourList();

	Colours(); // Constructor

private:

	glm::vec3 m_ColourList[7];	// Stores array of vector 3 representing colour list
};
#endif
