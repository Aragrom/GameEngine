#include "FontManager.h"

FontManager* FontManager::pInstance = NULL;

//Singleton Design Pattern
FontManager* FontManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new FontManager();
	}
	return FontManager::pInstance;
}

// Constructor
FontManager::FontManager()
{

}

FontManager::~FontManager()	// Destructor.
{
	deleteFont();
}
void FontManager::addFont(LPCSTR fontName, LPCSTR fileName, int fontSize)  // add font to the Font collection
{
	if (!getFont(fontName))
	{
		Font * newFont = new Font(fileName, fontSize);
		gameFonts.insert(make_pair(fontName, newFont));
	}
}

Font* FontManager::getFont(LPCSTR fontName)	// return the font for use
{
	map<LPCSTR, Font*>::iterator theFont = gameFonts.find(fontName);
	if (theFont != gameFonts.end())
	{
		return theFont->second;
	}
	else
	{
		return NULL;
	}
}

void FontManager::deleteFont()	// delete font.
{
	for (map<LPCSTR, Font*>::const_iterator theFont = gameFonts.begin(); theFont != gameFonts.end(); theFont++)
	{
		delete theFont->second;
	}
}
