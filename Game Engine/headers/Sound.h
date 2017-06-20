/*
==========================================================================
Sound.h
==========================================================================
*/

#ifndef _SOUND_H
#define _SOUND_H

// OpenGL Headers
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Sound
{
public:
	Sound();
	~Sound();

	void loadWAVFile(LPCSTR filename);		// Load the sound using an address
	void playAudio( ALboolean sndLoop);		// Set to play on sound on loop
	void stopAudio();						// Set this audio sound playing
	void cleanUp();							// Manage resources

private:

	// Custom Sound Structure
	struct FMTCHUNK {
		short format;
		short channels;
		unsigned long srate;
		unsigned long bps;
		short balign;
		short samp;
	};

	// Load the sound using an address
	void LoadWAVInfo(ifstream &filename, string &name, unsigned int &size);

	char*        m_OALData;			// Data for the buffer
	ALenum       m_OALFormat;		// Buffer format
	ALsizei      m_OALFrequency;	// Frequency
	long         m_OALBufferLen;	// Bit depth
	int			 m_OALChannels;		// Channels
	int			 m_OALSize;			// Size
	int			 m_OALBitRate;		// Bit Rate
	float        m_OALLength;		// Length
	ALboolean    m_OALLoop;			// Loop
	unsigned int m_OALSource;		// Source
	ALuint       m_OALBuffer;		// Buffer
	ALboolean    m_OALbEAX;			// For EAX 2.0 support
	ALboolean    m_alLoop;			// Loop

};
#endif