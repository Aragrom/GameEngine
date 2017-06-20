#include "Keyboard.h"

// Constructor
Keyboard::Keyboard()
{
	// initiate all key states to false
    for(int i=0;i<MAX_NO_KEYS;i++)
    {
        keysDown[i]=false;
        keysUp[i]=false;
    }
}

// Deconstructor
Keyboard::~Keyboard()
{
    
}

// Update buttons states
void Keyboard::update()
{
	// Reset all button states
    for(int i=0;i<MAX_NO_KEYS;i++)
    {
        keysDown[i]=false;
        keysUp[i]=false;
    }
    
}

// Set integer representing a key DOWN
void Keyboard::setKeyDown(short index)
{
    keysDown[index]=true;
}

// Set integer representing a key UP
void Keyboard::setKeyUp(short index)
{
    keysUp[index]=true;
}

// Get integer representing a key DOWN
bool Keyboard::isKeyDown(short index)
{
    return keysDown[index];
}

// Get integer representing a key UP
bool Keyboard::isKeyUp(short index)
{
    return keysUp[index];
}