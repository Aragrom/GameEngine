/*
==========================================================================
Font.h
==========================================================================
*/

#ifndef _CFONT_H
#define _CFONT_H

// OpenGL Headers
#include "GameConstants.h"

using namespace std;

class Font
{
public:

	// Getter
	FTFont* getFont();

	Font();		// Constructor
	Font(LPCSTR fontFileName, int fontSize);	// Constructor - Uses Font address and assigns font size
	~Font();	// Deconstructor

	void printText(LPCSTR text, FTPoint textPos);							// Render text to active buffer (TEXT, TEXT_POSITION)
	void printText(LPCSTR text, FTPoint textPos, Colour3f textColour);		// Render text to active buffer (Uses Colour)

private:

	FTFont* theFont;	// Pointer to Font Object
};
#endif