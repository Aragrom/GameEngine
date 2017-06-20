#ifndef OPENGLLOADER_H
#define OPENGLLOADER_H

#include "GameConstants.h"

class OpenGLLoader
{
public:

	void cleanUp();
	void checkForErrors();
	void initWindow(int width, int height, bool fullscreen);
	void initOpenGL();
	void setViewport(int width, int height);
	void handleEvents();
	void setOrtho2D(int width, int height);
	void setProjection3D(int width, int height);
	void onResize(int width, int height);

	SDL_Window* getWindow();
	SDL_GLContext getContext();
	bool isActive();

private:

	bool bIsActive = true;
	SDL_Window *window = NULL;
	SDL_GLContext glcontext = NULL;
	SDL_Event event;

};
#endif
