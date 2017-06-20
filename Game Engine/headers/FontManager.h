/*
==========================================================================
FontManager.h
==========================================================================
*/
#ifndef _CFONTMGR_H
#define _CFONTMGR_H
#include "GameConstants.h"
#include "Font.h"

class FontManager
{
public:

	//Getter
	static FontManager* getInstance();
	Font* getFont(LPCSTR fontName);		// return the font for use

	FontManager();		// Constructor
	~FontManager();		// Destructor.
	void addFont(LPCSTR fontName, LPCSTR fileName, int fontSize);	// add font to the Font collection
	void deleteFont();	// delete font.

private:

	static FontManager* pInstance;	// STATIC Instance of FontManager
	map<LPCSTR, Font*> gameFonts;	// Map representing a list of game fonts (FONT.NAME, FONT.CLASS)
};

#endif