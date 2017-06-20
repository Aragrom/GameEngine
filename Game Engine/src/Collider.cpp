#include "GameConstants.h"
// Base class for BoxCollider and SphereCollider

// Constructor
Collider::Collider()
{
	m_Active = true;
	m_Type = "Collider";
	m_ColliderType = "";
}

// Deconstructor
Collider::~Collider()
{

}



