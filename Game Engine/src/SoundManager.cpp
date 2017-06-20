/*
==================================================================================
cSoundMgr.cpp
==================================================================================
*/

#include "SoundManager.h"
#include "Input.h"

SoundManager* SoundManager::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
SoundManager::SoundManager()
{
	createContext();
}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
SoundManager* SoundManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new SoundManager();
	}
	return SoundManager::pInstance;
}

void SoundManager::createContext()
{
	m_OALDevice = alcOpenDevice(NULL);
	if (m_OALDevice)
	{
		//Create a context
		m_OALContext = alcCreateContext(m_OALDevice, NULL);

		//Set active context
		alcMakeContextCurrent(m_OALContext);
	}
}

void SoundManager::add(LPCSTR sndName, LPCSTR fileName)
{
	if (!getSnd(sndName))
	{
		Sound * newSnd = new Sound();
		newSnd->loadWAVFile(fileName);
		gameSnds.insert(make_pair(sndName, newSnd));
	}
}

Sound* SoundManager::getSnd(LPCSTR sndName)
{
	map<LPCSTR, Sound*>::iterator snd = gameSnds.find(sndName);
	if (snd != gameSnds.end())
	{
		return snd->second;
	}
	else
	{
		return NULL;
	}
}

void SoundManager::deleteSnd()
{
	for (map<LPCSTR, Sound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)
	{
		delete snd->second;
	}
}


SoundManager::~SoundManager()
{
	m_OALContext = alcGetCurrentContext();

	//Get device for active context
	m_OALDevice = alcGetContextsDevice(m_OALContext);

	//Release context(s)
	alcDestroyContext(m_OALContext);

	//Close device
	alcCloseDevice(m_OALDevice);

}
