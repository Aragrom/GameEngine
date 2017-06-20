#ifndef Keyboard_h
#define Keyboard_h

class Keyboard
{
public:

    Keyboard();		// Constructor
    ~Keyboard();	// Deconstructor
    
	// Setters
    void setKeyDown(short keyCode);
    void setKeyUp(short keyCode);
    
	// Manage Keyboard Button States
    bool isKeyDown(short keyCode);
    bool isKeyUp(short keyCode);
    
    void update();

private:

    const static short MAX_NO_KEYS=256; // Max number of keys for keyboard
    bool keysDown[MAX_NO_KEYS];			// Array of Keyboard Buttons with 'Down' State
    bool keysUp[MAX_NO_KEYS];			// Array of Keyboard Buttons with 'Up' State
};


#endif
