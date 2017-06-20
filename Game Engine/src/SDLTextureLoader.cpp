#include "SDLTextureLoader.h"

//Will clean up the surface as well;
GLuint convertSDLSurfaceToGLTexture(SDL_Surface * surface)
{
	GLuint textureID = 0;
    GLint  nOfColors = surface->format->BytesPerPixel;
	GLenum texture_format = GL_RGB;
    GLenum internalFormat=GL_RGB8;
	if (nOfColors == 4)     // contains an alpha channel
	{
		if (surface->format->Rmask == 0x000000ff){
			texture_format = GL_RGBA;
            internalFormat=GL_RGBA8;
        }
		else{
			texture_format = GL_BGRA;
            internalFormat=GL_RGBA8;
        }
	}
	else if (nOfColors == 3)     // no alpha channel
	{
		if (surface->format->Rmask == 0x000000ff){
			texture_format = GL_RGB;
            internalFormat=GL_RGB8;
        }
		else
        {
			texture_format = GL_BGR;
            internalFormat=GL_RGB8;
        }
	}
	glGenTextures(1, &textureID);																// Generate the texture
	glBindTexture(GL_TEXTURE_2D, textureID);													// Bind the Texture
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, surface->w, surface->h, 0, texture_format,	// Defne the texture properties
		GL_UNSIGNED_BYTE, surface->pixels);

	SDL_FreeSurface(surface);	// Memory Manage

	return textureID;			// return GLuint representing the texture ID
}

// Using a string representing a texture address 
GLuint loadTextureFromFile(const std::string& filename)
{
	GLuint textureID = 0;												// Texture ID
	SDL_Surface *imageSurface = IMG_Load(filename.c_str());				// Load using IMG the texture as an SDL_Surface

	// Check for errors
	if (!imageSurface){
		std::cout << "Can' Load image " << filename << " " << IMG_GetError();
		return textureID;
	}

	textureID = convertSDLSurfaceToGLTexture(imageSurface);				// Conversion of type

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);									// Generate Mip Map for the texture
	return textureID;													// return GLuint representing the texture ID
}

// Using a string representing the address for the Font, a font size and the 'text' to be displayed
GLuint loadTextureFromFont(const std::string& fontFilename, int pointSize, const std::string& text)
{
	GLuint textureID = 0;												// Variable holding the texture ID as a GLuint
	TTF_Font * font = TTF_OpenFont(fontFilename.c_str(),pointSize);		// The font variable
	if (!font)	// Check for errors
	{
		std::cout << "Unable to load font " << fontFilename << " " << TTF_GetError();
        return textureID;
	}

	// Render the text to the SDL_Surface
	SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), { 255, 255, 255 });

	textureID=convertSDLSurfaceToGLTexture(textSurface);	// Convert SDL_Surface to GLuint

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

	TTF_CloseFont(font);	// Memory manage

	return textureID;		//return GLuint representing the texture ID
}

void loadCubeMapSide(const std::string& filename, GLenum cubeSide)
{
	SDL_Surface *imageSurface = IMG_Load(filename.c_str());		// Load using IMG as a SDL_Surface

	GLint  nOfColors = imageSurface->format->BytesPerPixel;		// Get number of colours
	GLenum texture_format = GL_RGB;								// Define possible format
	GLenum internalFormat = GL_RGB8;							// Define possible format

	// Handle colour format
	if (nOfColors == 4)			// contains an alpha channel
	{
		if (imageSurface->format->Rmask == 0x000000ff)
		{
			texture_format = GL_RGBA;
			internalFormat = GL_RGBA8;
		}
		else
		{
			texture_format = GL_BGRA;
			internalFormat = GL_RGBA8;
		}
	}
	else if (nOfColors == 3)	// no alpha channel
	{
		if (imageSurface->format->Rmask == 0x000000ff)
		{
			texture_format = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else
		{
			texture_format = GL_BGR;
			internalFormat = GL_RGB8;
		}
	}

	// Specifiy two-dimension array for texture
	glTexImage2D(cubeSide, 0, internalFormat, imageSurface->w, imageSurface->h, 0, texture_format, GL_UNSIGNED_BYTE, imageSurface->pixels);

	SDL_FreeSurface(imageSurface);		// Memory Manage
}