#ifndef Material_h
#define Material_h

#include <GL/glew.h>

#include <glm/glm.hpp>
using glm::vec4;

#include <string>

#ifdef __APPLE__
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#endif

#include "Component.h"

class BaseMaterial :public Component
{
public:

	BaseMaterial() { m_Type = "BaseMaterial"; };	// Constructor
	virtual ~BaseMaterial(){ }						// Deconstructor

	virtual void bind(){};							// Virtual
	virtual void unbind(){};						// Virtual

	bool loadShader(const std::string& vsFilename, const std::string& fsFilename);
	GLint getUniformLocation(const std::string& name);

protected:

	GLuint m_ShaderProgram;		// Shader Program
};

class Material :public BaseMaterial
{
public:

    Material();				// Constructor
    ~Material();			// Deconstructor
    
    void destroy();			// Memory Manage    
    void bind();			// Bind Shader Program and texture to pipeline
	
	// Getters
	vec4& getAmbientColour();
	vec4& getDiffuseColour();
	vec4& getSpecularColour();
	float getSpecularPower();
	GLuint getDiffuseMap();
	GLuint getSpecularMap();
	GLuint getBumpMap();
	GLuint getHeightMap();

	// Setters
	void setAmbientColour(float r, float g, float b, float a);
	void setDiffuseColour(float r, float g, float b, float a);
	void setSpecularColour(float r, float g, float b, float a);
	void setSpecularPower(float power);

	// Load textures using string and store it as its texture variable
	void loadDiffuseMap(const std::string& filename);
	void loadSpecularMap(const std::string& filename);
	void loadBumpMap(const std::string& filename);
	void loadHeightMap(const std::string& filename);

private:

	vec4 m_AmbientColour;		// Colour under light
	vec4 m_DiffuseColour;		// Base Colour
	vec4 m_SpecularColour;		// Highlight colour
	float m_SpecularPower;		// Amount of highlight

	// GLuints representing loaded textures
	GLuint m_DiffuseMap;
	GLuint m_SpecularMap;
	GLuint m_BumpMap;
	GLuint m_HeightMap;
};

#endif
