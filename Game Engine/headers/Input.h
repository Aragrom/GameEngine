#ifndef Input_h
#define Input_h

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif WIN32
#include <SDL.h>
#endif

#include "Keyboard.h"
#include "Mouse.h"
#include "Joypad.h"

#include <string>
#include <vector>

class Input
{
public:

	// Getters
	Keyboard * getKeyboard() { return m_Keyboard; };
	Mouse * getMouse() { return m_Mouse; };
	int getNumberofAttachedJoypads() { return m_AttachedJoypads.size(); };
	Joypad * getJoypad(int playerIndex) { return m_AttachedJoypads[playerIndex]; }
	static Input& getInput() { static Input input; return input; }

    Input();	// Constructor
    ~Input();	// Deconstructor
    
    bool init(const std::string& inputDBFilename);		// Initialise joypads connected, mouse and keyboard
	void destroy();										// memory manage
    void update();										// 

private:

	Keyboard * m_Keyboard;	// Link Keyboard Object
    Mouse * m_Mouse;		// Link Mouse Object
	std::vector<Joypad*> m_AttachedJoypads;	// Representing vector of atatched JoyPads Objects
};


#endif
