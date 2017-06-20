#include "Joypad.h"

// Constructor
Joypad::Joypad(SDL_GameController * SDLController)
{
	m_SDLController = SDLController;
	for (int i = 0; i < MAX_NO_OF_BUTTONS; i++)
	{
		m_ButtonsUp[i] = false;
		m_ButtonsDown[i] = false;
	}

	m_LeftThumbstick = vec2(0.0f, 0.0f);
	m_RightThumbstick = vec2(0.0f, 0.0f);
	m_LeftTrigger = 0;
	m_RightTrigger = 0;
	m_InvertAxis = true;
}

// Deconstructor
Joypad::~Joypad()
{
	SDL_GameControllerClose(m_SDLController);
}

// Toggle short representing a button UP (2 array represent buttons up and buttons down)
void Joypad::setButtonUp(short buttonIndex)
{
	m_ButtonsUp[buttonIndex] = true;
	m_ButtonsDown[buttonIndex] = false;
}

// Toggle short representing a button DOWN
void Joypad::setButtonDown(short buttonIndex)
{
	m_ButtonsUp[buttonIndex] = false;
	m_ButtonsDown[buttonIndex] = true;
}

// Based on short representing the analog axis and an amount to move it
void Joypad::setAxisValue(short axisID, int value)
{
	if (axisID == Joypad::AxisID::LEFT_AXIS_HORIZONTAL)
	{
		m_LeftThumbstick.x = value; // update value
	}
	else if (axisID == Joypad::AxisID::LEFT_AXIS_VERTICAL)
	{
		m_LeftThumbstick.y = value;
		if (m_InvertAxis)
			m_LeftThumbstick.y *= -1;
	}
	if (axisID == Joypad::AxisID::RIGHT_AXIS_HORIZONTAL)
	{
		m_RightThumbstick.x = value;
	}
	else
	{
		m_RightThumbstick.y = value;
		if (m_InvertAxis)
			m_LeftThumbstick.y *= -1;
	}
	if (axisID == Joypad::AxisID::LEFT_TRIGGER)
	{
		m_LeftTrigger = value;
	}
	else if (axisID==Joypad::AxisID::RIGHT_TRIGGER)
	{
		m_RightTrigger = value;
	}
}