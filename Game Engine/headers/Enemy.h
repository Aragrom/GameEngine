/*
==========================================================================
Enemy.h
==========================================================================
*/

#ifndef _enemy_h
#define _enemy_h

#include "GameConstants.h"
#include <vector>

class Enemy
{
public:

	//Setter
	void setGameObject(GameObject *go) { m_gameObject = go; }
	void setTarget(GameObject *go) { m_goTarget = go; }
	void setDistanceToEngage(float f) { m_fDistanceToEngage = f; }

	Enemy();	// Constructor
	~Enemy();	// Deconstructor

	void update();							// Used to call enemy functionality
	float calculateDistanceToTarget();		// Using the this gameobjects target variable use distance formula to compare with engage distance
	void calculateDirectionToMove();		// Using the this gameobjects target variable see which distance is greater (X or Z - No vertical movement) 
	void move();							// Move the enemy towards the player using an integer representing a direction


private:
	
	GameObject *m_gameObject;								// attached to this gameobject
	GameObject *m_goTarget;									// GameObject representing the player, used to check distance from self

	enum eMoveDirections { NORTH, EAST, SOUTH, WEST };
	bool m_bIsMoving;										// Set true to make player move
	int m_iDirection;										// Represents 0,1,2,3 for direction NORTH,EAST,SOUTH,WEST
	float m_fDistanceToEngage;								// How close player has to be for enemy to engage

};

#endif
