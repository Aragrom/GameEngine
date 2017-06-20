#ifndef _CUSTOMSHAPE_H
#define _CUSTOMSHAPE_H

#include "Vertex.h"
#include "GameObject.h"
#include "GL\glew.h"

class CustomShape
{

public:

	CustomShape();					// Constructor
	void init(GameObject * go);		// Initiate CustomShape preparing Vertices from gameObject.transform.position
	void generateMesh(GameObject * go, GLuint indices[], Vertex vertices[], int iIdenices, int iVerticies);		// Load Mesh with Vertex and Indices Data
	void sprite(GameObject * go);	// Initiate CustomShape preparing Vertex and indices data for mesh component

	glm::vec3 m_Faces[24];		// Array of Vector 3 representing Faces
	GLuint m_Indices[36];		// Array of GLuint representing the CustomShape's indices

	std::vector<glm::vec3> m_vertices;		// Stores Vector of vector 3 representing the CustomShape's vertices
	std::vector<glm::vec3> m_colourList;	// Stores Vector of vector 3 representing the CustomShape's Colour List
};

#endif

