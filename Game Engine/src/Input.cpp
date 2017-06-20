#include "Input.h"

// Constructor
Input::Input()
{
    m_Mouse=NULL;
    m_Keyboard=NULL;
}

// Deconstructor
Input::~Input()
{
	
}

// Destroy
void Input::destroy()
{
	// Destroy Vector of 'attached joypads'
	auto iter = m_AttachedJoypads.begin();
	while (iter != m_AttachedJoypads.end())
	{
		if ((*iter))
		{
			delete (*iter);
			iter = m_AttachedJoypads.erase(iter);
		}
		else
			iter++;
	}
	m_AttachedJoypads.clear();
    
	// if mouse and keyboard exists then delete them
    if (m_Mouse)
    {
        delete m_Mouse;
        m_Mouse=NULL;
    }
    if (m_Keyboard)
    {
        delete m_Keyboard;
        m_Keyboard=NULL;
    }
}

void Input::update()
{
    m_Keyboard->update();
}

bool Input::init(const std::string& inputDBFilename)
{
    m_Keyboard=new Keyboard();												// Instantiate Keyboard object
    m_Mouse=new Mouse();													// Instantiate Mouse object
	SDL_GameControllerAddMappingsFromFile(inputDBFilename.c_str());			// Define controller mapping
	int numOfJoypads = SDL_NumJoysticks();									// for number of controller connected
	for (int i = 0; i < numOfJoypads; i++)
	{
		//Is the joypad able to use the new controller interface
		if (SDL_IsGameController(i))
		{
			SDL_GameController *controller = SDL_GameControllerOpen(i);		// Initialise SDL controller for event handling
			Joypad * joypad = new Joypad(controller);						// Initialise Joypad class and link with SDL controller object
			m_AttachedJoypads.push_back(joypad);							// Attack joypad for tracking and management
		}
	}

    return true;	// if we get here init successful
}