#include "Component.h"
#include "GameObject.h"

// Constructor
Component::Component()
{
    m_Type="Component";
    m_Name="Component";
    m_Parent=NULL;
    m_Active=true;
}

// Deconstructor
Component::~Component()
{
    
}

// Virtual
void Component::init()
{
    
}

// Virtual
void Component::update()
{
    
}

// Virtual
void Component::render()
{
    
}

// Virtual
void Component::destroy()
{
    
}