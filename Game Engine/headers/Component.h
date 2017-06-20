#ifndef Component_h
#define Component_h

#include <string>

class GameObject;

class Component
{
public:

	// Getters
	const std::string& getName() { return m_Name; }
	const std::string& getType() { return m_Type; }
	GameObject *getParent() { return m_Parent; }
	bool isActive() { return m_Active; }

	// Setter
	void toggleActive() { m_Active = !m_Active; }
	void setParent(GameObject *object) { m_Parent = object; }
	void setName(const std::string& name) { m_Name = name; }

    Component();			// Constructor
    virtual ~ Component();	// Deconstructor
    
	// VIRTUAL functions
    virtual void init();    
    virtual void update();    
    virtual void render();    
    virtual void destroy();

protected:

    std::string m_Type;			// Stores Component Type property
    std::string m_Name;			// Stores String property for component name
    bool m_Active;				// Component Active State
    GameObject * m_Parent;		// GameObject that owns the component
};

#endif
