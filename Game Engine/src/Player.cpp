#include "Player.h"

// Constructor
Player::Player() 
{
	m_bIsFalling = true;
	m_fFallVelocity = 0.01f;
	m_iHealth = 2;
}

// Deconstructor
Player::~Player()
{

}

// Using interger passed lower health. Return state on dead or alive based on players health
bool Player::takeDamage(int iDmg) 
{
	m_iHealth -= iDmg;
	std::cout << "Damage Taken! Health .." << m_iHealth << std::endl;
	if (m_iHealth < 0) return true;
	else return false;
}

// Generates primitive physics for gravity
void Player::update()
{
	// if falling and camera is not in 'Scene View Mode'
	if (m_bIsFalling && static_cast<BasicCameraController*>(m_gameObject->getCamera())->getViewMode() == false)
	{
		moveUsingGravity();		// Sets player transfrom position based on a float which increases over time
		checkOutOfBounds();		// Check player transform position for out of bounds - game reset
	}
}

// Reset fall velocity and set falling state
void Player::setIsFalling(bool b)
{
	if (m_bIsFalling != b) m_fFallVelocity = 0.01f;
	m_bIsFalling = b;
}

// Sets player transform position and camera components look at vec 3 (based on a float which increases over time)
void Player::moveUsingGravity()
{
	vec3 v3 = m_gameObject->getTransform()->getPosition();		// Current Player Position
	vec3 v3Camera = m_gameObject->getCamera()->getLookAt();		// Current camera look at vector 3

	// Define and set new player position
	v3 = v3 - vec3(0.0f, 0.01f * m_fFallVelocity, 0.0f);
	m_gameObject->getTransform()->setPosition(v3.x, v3.y, v3.z);

	// Define and set new camera look at vector 3
	v3Camera = v3Camera - vec3(0.0f, 0.01f * m_fFallVelocity, 0.0f);
	m_gameObject->getCamera()->setLook(v3Camera.x, v3Camera.y, v3Camera.z);

	m_fFallVelocity += 0.5f;									// Increment fall velocity - No limit -
}

// Check player transform position for out of bounds - game reset
void Player::checkOutOfBounds() 
{
	vec3 v3PlayerPosition = m_gameObject->getTransform()->getPosition(); // Based on current position
	if (v3PlayerPosition.y < -10.0f)	// Check if .y position is lower than -10.0f
	{
		m_gameObject->getTransform()->setPosition(V3_START_POSITION.x, V3_START_POSITION.y, V3_START_POSITION.z);	// Reset Player position
		m_gameObject->getCamera()->setLook(V3_START_POSITION.x, V3_START_POSITION.y, V3_START_POSITION.z - 1.0f);	// Reset Cameras look at position
		static_cast<BasicCameraController*>(m_gameObject->getCamera())->setLookAngle(0.0f);							// Cast and reset Basic Camera Controller's component 'Angle'
		m_iHealth = 2;																								// Reset Player Health

		std::cout << "RESET GAME" << std::endl;																		// Message User

		BasicCameraController *bsc = static_cast<BasicCameraController*>(m_gameObject->getCamera());				// Cast and get the camera controller component

		if (bsc->getLookingAtTarget())			// if Locked onto target (which happens on level completion)
		{		
			bsc->setLookingAtTarget(false);		// Reset Basic Camera Controllers lock on state
			m_fFallVelocity = 0.0f;				// Reset fall velocity as the player will be falling so fast it will pass through colliders
		}
	}
}