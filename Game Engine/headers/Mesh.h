#ifndef Mesh_h
#define Mesh_h

#include <GL/glew.h>

#ifdef __APPLE__
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#endif

#include "Component.h"

class Sphere;

class Mesh:public Component
{
public:

	// Getters
	int Mesh::getVertexCount() { return m_VertexCount; }

	// Setters
	int Mesh::getIndexCount() {	return m_IndexCount; }

    Mesh();		// Constructor
    ~Mesh();	// Deconstructor
    
    void init();		// Generate Shader program and buffers
    void destroy();		// Memory clean up
    void bind();		// Bind buffers to pipeline
    
    void copyVertexData(int count,int stride,void ** data);		// For handling Vertex Data
    void copyIndexData(int count,int stride,void ** data);		// For handling Index Data

private:

    int m_VertexCount;	// Amount of Vertex's
    int m_IndexCount;	// Amount of Indices
    GLuint m_VBO;		// Vertex Buffer Object
    GLuint m_EBO;		// Element Buffer Object
    GLuint m_VAO;		// Vertex Array Object
};

#endif
