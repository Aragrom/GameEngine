#ifndef SDLTEXTURELOADER_H
#define SDLTEXTURELOADER_H

#include <GL/glew.h>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif WIN32
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif


#include <iostream>
#include <string>

GLuint convertSDLSurfaceToGLTexture(SDL_Surface * surface);

GLuint loadTextureFromFile(const std::string& filename);
//this shouldn't be used for realtime use, build on startup!
GLuint loadTextureFromFont(const std::string& fontFilename, int pointSize, const std::string& text);

void loadCubeMapSide(const std::string& filename, GLenum cubeSide);

#endif