#ifndef Mouse_h
#define Mouse_h

class Mouse
{
public:

	// Setters
	void setMousePosition(int absX, int absY, int relX, int relY);
	void setMouseButtonDown(int buttonIndex);
	void setMouseButtonUp(int buttonIndex);

	// Getters
	bool isButtonDown(int buttonIndex);
	bool isButtonUp(int buttonIndex);
	int getRelativeMouseX() { return m_RelMouseX; };
	int getRelativeMouseY() { return m_RelMouseY; };

    Mouse();	// Constructor
    ~Mouse();	// Deconstructor
    
    void update();
    
private:

    static const int MAX_NO_OF_BUTTONS=3;
    int m_AbsMouseX;
    int m_AbsMouseY;
    int m_RelMouseX;
    int m_RelMouseY;
    bool m_MouseButtonsDown[MAX_NO_OF_BUTTONS];
    bool m_MouseButtonsUp[MAX_NO_OF_BUTTONS];
};

#endif
