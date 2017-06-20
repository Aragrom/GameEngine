#include "Mouse.h"

// Constructor
Mouse::Mouse()
{
    m_AbsMouseX=0;
    m_AbsMouseY=0;
    m_RelMouseX=0;
    m_RelMouseY=0;
    for (int i=0;i<MAX_NO_OF_BUTTONS;i++)
    {
        m_MouseButtonsDown[i]=false;
        m_MouseButtonsUp[i]=false;
    }
}

// Deconstructor
Mouse::~Mouse()
{
    
}

void Mouse::update()
{
    
}

// Set mouse position
void Mouse::setMousePosition(int absX, int absY, int relX, int relY)
{
    m_AbsMouseX=absX;
    m_AbsMouseY=absY;
    m_RelMouseX=relX;
    m_RelMouseY=relY;
}

// Set mouse buttons state DOWN for the given integer index representing a key (toggle lists)
void Mouse::setMouseButtonDown(int buttonIndex)
{
    m_MouseButtonsDown[buttonIndex]=true;
    m_MouseButtonsUp[buttonIndex]=false;
}

// Set mouse buttons state DOWN for the given integer index representing a key (toggle lists)
void Mouse::setMouseButtonUp(int buttonIndex)
{
    m_MouseButtonsDown[buttonIndex]=false;
    m_MouseButtonsUp[buttonIndex]=true;
}

// Set mouse buttons state UP for the given integer index representing a key in the array of buttons
bool Mouse::isButtonDown(int buttonIndex)
{
    return m_MouseButtonsDown[buttonIndex];
}

// Set mouse buttons state UP for the given integer index representing a key in the array of buttons
bool Mouse::isButtonUp(int buttonIndex)
{
    return m_MouseButtonsUp[buttonIndex];
}