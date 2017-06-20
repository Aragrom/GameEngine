/*
==========================================================================
SoundManager.h
==========================================================================
*/

#ifndef _SOUNDMGR_H
#define _SOUNDMGR_H

// OpenGL Headers
#include "GameConstants.h"
#include "Sound.h"

class SoundManager
{
public:

	//Getter
	Sound* getSnd(LPCSTR sndName);

	void add(LPCSTR sndName, LPCSTR fileName);	// Add the sound using name and sound address
	void deleteSnd();							// Manage sounds
	static SoundManager* getInstance();			// Get instance of Sound Manager

private:

	static SoundManager* pInstance;		// STATIC Instance of Sound Manager
	ALCcontext *m_OALContext;			// Sound Manager Context
	ALCdevice *m_OALDevice;				// Sound Manager Device

protected:

	SoundManager();		// Constructor
	~SoundManager();	// Deconstructor
	map <LPCSTR, Sound*> gameSnds;		// Map representing a list of game sounds (SOUND.NAME, SOUND.CLASS)
	void createContext();				// Instantiate Sound Manager Context
};
#endif