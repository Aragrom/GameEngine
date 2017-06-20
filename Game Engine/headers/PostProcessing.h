#ifndef POST_PROCESSING_H
#define POST_PROCESSING_H

#include <GL/glew.h>
#include <string>

#ifdef __APPLE__
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#elif WIN32
#include <SDL_opengl.h>
#include <gl/GLU.h>
#endif


class PostProcessing
{
public:
	PostProcessing();
	~PostProcessing();

	void init(int width, int height,std::string& vertexShaderFilename,std::string& fragmentShaderFilename);
	
	void bind();

	void preDraw();
	void draw();
	void postDraw();

	void destroy();

	GLint getUniformVariableLocation(const std::string& name);

private:
	void createShader(std::string& vertexShaderFilename, std::string& fragmentShaderFilename);
	void createFullScreenQuad();
	void createFramebuffer(int width,int height);

	GLuint m_FrameBufferObject;
	GLuint m_DepthBufferObject;
	GLuint m_FBOTexture;

	GLuint m_FullScreenVBO;

	GLuint m_PostProcessingProgram;
	int m_Width;
	int m_Height;
};

#endif