#include "GameConstants.h"

//Getters
SDL_Window* OpenGLLoader::getWindow() { return window; }
SDL_GLContext OpenGLLoader::getContext() { return glcontext; }
bool OpenGLLoader::isActive() { return bIsActive; }

// Memory Management
void OpenGLLoader::cleanUp() 
{
	//Order is important
	SDL_GL_DeleteContext(glcontext);	// Destroy SDL Context
	SDL_DestroyWindow(window);			// SDL Destroys the window
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

// Check for errors found by SDL
void OpenGLLoader::checkForErrors()
{
	GLenum error;
	do {
		error = glGetError();
	} while (error != GL_NO_ERROR);
}

//Global functions
void OpenGLLoader::initWindow(int width, int height, bool fullscreen)
{
	//Create a window
	window = SDL_CreateWindow( 
		"OpenGL Game Engine",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		width,                        // width, in pixels
		height,                        // height, in pixels
		SDL_WINDOW_OPENGL           // flags
		);
}

void OpenGLLoader::onResize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// set the perspective with the appropriate aspect ratio
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0f, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLLoader::setOrtho2D(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glOrtho(45.0f, width, height, 0, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGLLoader::setProjection3D(int width, int height)
{
	onResize(width, height);
}

//Function to initialise OpenGL
void OpenGLLoader::initOpenGL()
{	
	//Ask for version 3.2 of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Problem: glewInit failed, something is seriously wrong.
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the depth buffer
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//The depth test to go
	glDepthFunc(GL_LEQUAL);

	//Turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//Function to set/reset viewport
void OpenGLLoader::setViewport( int width, int height )
{
	//make sure height is always above 1
	if ( height == 0 ) {
		height = 1;
	}
	
	//Setup viewport
	glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
}

// Handle SDL events
void OpenGLLoader::handleEvents()
{
	//While we still have events in the queue
	while (SDL_PollEvent(&event)) {

		switch (event.type)
		{
			case SDL_QUIT:
			{
				bIsActive = false;
				break;
			}
			case SDL_WINDOWEVENT_CLOSE:
			{
				bIsActive = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				Input::getInput().getKeyboard()->setKeyDown(event.key.keysym.sym);
				break;
			}
			case SDL_KEYUP:
			{
				Input::getInput().getKeyboard()->setKeyUp(event.key.keysym.sym);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				Input::getInput().getMouse()->setMousePosition(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				Input::getInput().getMouse()->setMouseButtonDown(event.button.button);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				Input::getInput().getMouse()->setMouseButtonUp(event.button.button);
				break;
			}
			case SDL_CONTROLLERAXISMOTION:
			{
				int controllerID = event.caxis.which;
				short axisID = event.caxis.axis;
				int axisValue = event.caxis.value;
				//filter results between -3200 and 3200(are in the ‘dead zone’)
				if (axisValue > Joypad::DeadzoneNeg && axisValue < Joypad::DeadzonePos)
				{
					axisValue = 0;
				}

				Input::getInput().getJoypad(controllerID)->setAxisValue(axisID, axisValue);

				break;
			}
			case SDL_CONTROLLERBUTTONDOWN:
			{
				int controllerID = event.cbutton.which;
				short buttonID = event.cbutton.button;

				Input::getInput().getJoypad(controllerID)->setButtonDown(buttonID);
				break;
			}
			case SDL_CONTROLLERBUTTONUP:
			{
				int controllerID = event.cbutton.which;
				short buttonID = event.cbutton.button;

				Input::getInput().getJoypad(controllerID)->setButtonUp(buttonID);
				break;
			}
		}
	}
}