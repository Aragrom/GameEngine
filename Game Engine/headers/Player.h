/*
==========================================================================
Enemy.h
==========================================================================
*/

#ifndef _player_h
#define _player_h

#include "GameConstants.h"
#include <vector>

class Player
{
public:

	//Setter
	void setGameObject(GameObject *go) { m_gameObject = go; }
	void setStartPosition(vec3 v3) { m_v3StartPosition = v3; }

	//Getter
	GameObject* getGameObject() { return m_gameObject; }
	bool getIsFalling() { return m_bIsFalling; }
	int getPlayerHealth() { return m_iHealth; }

	Player();
	~Player();

	void update();
	void moveUsingGravity();
	bool takeDamage(int iDmg);
	void checkOutOfBounds();
	void setIsFalling(bool b);

private:

	GameObject *m_gameObject;
	vec3 m_v3StartPosition;
	float m_fFallVelocity;
	bool m_bIsFalling;
	int m_iHealth;
};

#endif
