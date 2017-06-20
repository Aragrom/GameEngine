#include "PostProcessing.h"
#include "Shader.h"

// Constructor
PostProcessing::PostProcessing()
{
	m_FrameBufferObject=0;
	m_DepthBufferObject=0;
	m_FBOTexture=0;
	m_FullScreenVBO=0;
	m_PostProcessingProgram=0;
}

// Deconstructor
PostProcessing::~PostProcessing()
{

}

// Initalise Shader Program, Frame Buffer and full screen quad for a texture
void PostProcessing::init(int width, int height, std::string& vertexShaderFilename, std::string& fragmentShaderFilename)
{
    m_Width=width;														// Define frame buffer's width
    m_Height=height;													// Define frame buffer's height
	createFramebuffer(width,height);									// Create the frame buffer
	createShader(vertexShaderFilename, fragmentShaderFilename);			// Create shader program
	createFullScreenQuad();												// Create full screen quad (full screen texture)
}

// Create shader program
void PostProcessing::createShader(std::string& vertexShaderFilename, std::string& fragmentShaderFilename)
{
	GLuint vertexShaderProgram = 0;															// Instantiate Shader Program variable
	vertexShaderProgram = loadShaderFromFile(vertexShaderFilename, VERTEX_SHADER);			// set variable to Vertex Shader

	GLuint fragmentShaderProgram = 0;
	fragmentShaderProgram = loadShaderFromFile(fragmentShaderFilename, FRAGMENT_SHADER);	// set variable to Fragment Shader

	m_PostProcessingProgram = glCreateProgram();											// SDL create shader program
	glAttachShader(m_PostProcessingProgram, vertexShaderProgram);							// ATTACH vertex shader
	glAttachShader(m_PostProcessingProgram, fragmentShaderProgram);							// ATTACH fragment shader
	glLinkProgram(m_PostProcessingProgram);													// LINK to programe to SDL
	checkForLinkErrors(m_PostProcessingProgram);											// Check for errors

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

// Create full screen quad that can hold texture representing the scene for post processing effects
void PostProcessing::createFullScreenQuad()
{
	/* init_resources */
	GLfloat vertices[] = {
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,
	};
	glGenBuffers(1, &m_FullScreenVBO);												// Generate Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_FullScreenVBO);									// Bind Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		// Set size and type of buffer data
	glBindBuffer(GL_ARRAY_BUFFER, 0);												// Bind the Buffer
}

void PostProcessing::createFramebuffer(int width, int height)
{
	// Frame Buffer
	glActiveTexture(GL_TEXTURE0);													// Activatate The Frame buffer Texture Object
	glGenTextures(1, &m_FBOTexture);												// Generate the texture from the Frame Buffer - the texture ID
	glBindTexture(GL_TEXTURE_2D, m_FBOTexture);										// Bind the frame buffer object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				// Define texture default parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);		// Assign width and height of texture
	glBindTexture(GL_TEXTURE_2D, 0);																// Bind texture

	// Depth buffer
	glGenRenderbuffers(1, &m_DepthBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Framebuffer to link everything together
	glGenFramebuffers(1, &m_FrameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferObject);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FBOTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferObject);
	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) 
	{
		std::cout << "Error in creating frame buffer found!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Bind the the Frame Buffer Object to the pipeline
void PostProcessing::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferObject);
	
}

// Creates Post Proccessor Program defining
void PostProcessing::preDraw()
{
	glActiveTexture(GL_TEXTURE0);					// Activate the texture which is the Frame Buffer
	glBindTexture(GL_TEXTURE_2D, m_FBOTexture);		// Bind the frame buffer object to the pipeline

	glUseProgram(m_PostProcessingProgram);			// Load the Program to use
	GLint textureLocation = glGetUniformLocation(m_PostProcessingProgram, "texture0");			// Get uniform from Program
	glUniform1i(textureLocation, 0);	// Assign

	GLint vertexPosLocation = glGetAttribLocation(m_PostProcessingProgram, "vertexPosition");	// Get attribute location from Program
	glEnableVertexAttribArray(0);		// Enable

	glBindBuffer(GL_ARRAY_BUFFER, m_FullScreenVBO);		// Bind the Full Screen vertex buffer object as an Array Buffer Object
	glVertexAttribPointer(
		vertexPosLocation,  // attribute
		2,                  // number of elements per vertex, here (x,y)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
		);

	glBindAttribLocation(m_PostProcessingProgram, vertexPosLocation, "vertexPosition");			// Bind the position to the
}

// After drawing disable Vertex Attribute Array Program
void PostProcessing::postDraw()
{
	glDisableVertexAttribArray(0);
}

// Using 'Triangle-Strip' draw the array buffer program
void PostProcessing::draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

// Memory management
void PostProcessing::destroy()
{
	glDeleteBuffers(1, &m_FullScreenVBO);
	glDeleteProgram(m_PostProcessingProgram);
	glDeleteRenderbuffers(1, &m_DepthBufferObject);
	glDeleteTextures(1, &m_FBOTexture);
	glDeleteFramebuffers(1, &m_FrameBufferObject);
}

// Get Uniform represented by a string from the Post Processing Program
GLint PostProcessing::getUniformVariableLocation(const std::string& name)
{
	return glGetUniformLocation(m_PostProcessingProgram, name.c_str());
}