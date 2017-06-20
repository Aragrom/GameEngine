#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#elif WIN32
#include <SDL_opengl.h>
#endif

#include "BasicCameraController.h"
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include  <math.h>
#include <iostream>
#include "Timer.h"
#include "Input.h"
#include "Light.h"
#include <glm/glm.hpp>
using glm::vec3;

//#include "GameConstants.h"

// Toggle bool state and based on state move camera
void BasicCameraController::toggleViewMode()
{
	m_bViewMode = !m_bViewMode;
	if (m_bViewMode && !checkCameraPosition()) 
	{
		v3SavedPosition = m_Parent->getTransform()->getPosition();
		v3SavedRotation = m_v3LookAt;
		m_Parent->getTransform()->setPosition(V3_VIEW_POSITION.x, V3_VIEW_POSITION.y, V3_VIEW_POSITION.z);
		m_v3LookAt = vec3(-300.0f, -100.0f, -500.0f);
	}

	if (!m_bViewMode && checkCameraPosition())
	{
		m_Parent->getTransform()->setPosition(v3SavedPosition.x, v3SavedPosition.y, v3SavedPosition.z);
		m_v3LookAt = v3SavedRotation;
	}
}

// Used to check if the camera position is equal to the 'scene viewer position'
bool BasicCameraController::checkCameraPosition()
{
	vec3 v3CamCurPos = m_Parent->getTransform()->getPosition();
	if (v3CamCurPos == V3_VIEW_POSITION) return true;
	else return false;
}

// Constructor
BasicCameraController::BasicCameraController()
{
	m_Type = "BasicCameraController";
	m_fAngle = 0.0f;
	m_fSinX = 0.0f,
	m_fCosZ = -1.0f;
	m_bLookAtTarget = false;
	m_iTargetIndex = 0;
	m_fObjectMoveSpeed = 1.0f;
	m_fObjectRotateSpeed = 1.0f;
	m_cAxis = 'x';
	m_iDir = 0;
	m_bCanMove = true;
	m_bViewMode = false;
	v3SavedPosition = vec3();
}

// Deconstructor
BasicCameraController::~BasicCameraController()
{

}

// Restricts movement when up against a wall
void BasicCameraController::setCanMove(bool b)
{
	m_bCanMove = b;
}

// Set the look at angle (angle used to generate view vector)
void BasicCameraController::setLookAngle(float f) 
{
	m_fAngle = f;
}

// Set lock on to target state
void BasicCameraController::setLookingAtTarget(bool b)
{
	if (b) std::cout << "\nCamera View: Locked (Press 'TAB' to iterate through GameObjects)" << std::endl;
	if (!b) std::cout << "\nCamera View: Unlocked" << std::endl;
	m_bLookAtTarget = b;
}

// Get state - if locking onto targets
bool BasicCameraController::getLookingAtTarget()
{
	return m_bLookAtTarget;
}

// Add GameObject to list of GameObjects that get be targetted
void BasicCameraController::addGameObjectToTargets(GameObject *go)
{
	m_vTargetGameObjects.push_back(go);
}

void BasicCameraController::iterateThroughTargets()
{	
	if (m_iTargetIndex < m_vTargetGameObjects.size()-1) m_iTargetIndex++;
	else m_iTargetIndex = 0;

	m_goTarget = m_vTargetGameObjects[m_iTargetIndex];
	std::cout << " - Targetted: " << m_vTargetGameObjects[m_iTargetIndex]->getName() << std::endl;
}

// Move cameras 'look at' and transform 'position' based on a string representing a direction
void BasicCameraController::moveCamera(std::string strDir)
{
	float fX = m_Parent->getTransform()->getPosition().x;
	float fY = m_Parent->getTransform()->getPosition().y;
	float fZ = m_Parent->getTransform()->getPosition().z;

	m_iDir = 0; //standing still
	
	if (strDir == "forward")
	{
		fX += m_fSinX * 0.1f;
		fZ += m_fCosZ * 0.1f;
		m_iDir = 1; //moving forward
	}

	if (strDir == "backward")
	{
		fX -= m_fSinX * 0.1f;
		fZ -= m_fCosZ * 0.1f;
		m_iDir = -1; //moving backward
	}

	if (strDir == "up")
	{
		fY += 0.01f;
	}

	if (strDir == "down")
	{
		fY -= 0.01f;
	}

	m_Parent->getTransform()->setPosition(fX, fY, fZ);			// set transfrom 'position'
	Camera::m_v3LookAt = vec3(fX + m_fSinX, fY, fZ + m_fCosZ);	// set 'look at'
}

// Rotate camera's 'look at' propety using current position and angle
void BasicCameraController::rotateCameraHorizontal(int iDir)
{	
	if (!m_bLookAtTarget)
	{
		if (iDir < 0)
		{
			m_fAngle -= 0.1f;
			m_fSinX = sin(m_fAngle);
			m_fCosZ = -cos(m_fAngle);
		}

		if (iDir > 0)
		{
			m_fAngle += 0.1f;
			m_fSinX = sin(m_fAngle);
			m_fCosZ = -cos(m_fAngle);
		}

		vec3 v3Pos = m_Parent->getTransform()->getPosition();
		m_v3LookAt = vec3(v3Pos.x + m_fSinX,
			v3Pos.y,
			v3Pos.z + m_fCosZ);
	}
}

// Move GameObject currently targetted based on a string representing a direction
void BasicCameraController::moveObject(std::string str)
{
	vec3 v3Pos = m_vTargetGameObjects[m_iTargetIndex]->getTransform()->getPosition();

	if (str == "forward")
	{
		float fX = v3Pos.x + m_fObjectMoveSpeed;
		m_vTargetGameObjects[m_iTargetIndex]->getTransform()->setPosition(fX, v3Pos.y, v3Pos.z);
		
	}
	if (str == "backward")
	{
		float fX = v3Pos.x - m_fObjectMoveSpeed;
		m_vTargetGameObjects[m_iTargetIndex]->getTransform()->setPosition(fX, v3Pos.y, v3Pos.z);
	}
	if (str == "right")
	{
		float fZ = v3Pos.z + m_fObjectMoveSpeed;
		m_vTargetGameObjects[m_iTargetIndex]->getTransform()->setPosition(v3Pos.x, v3Pos.y, fZ);
	}
	if (str == "left")
	{
		float fZ = v3Pos.z - m_fObjectMoveSpeed;
		m_vTargetGameObjects[m_iTargetIndex]->getTransform()->setPosition(v3Pos.x, v3Pos.y, fZ);
	}
}

// Rotate targetted GameObject based on a integer representing a direction
void BasicCameraController::rotateObject(int iDir)
{
	vec3 v3Rot = m_vTargetGameObjects[m_iTargetIndex]->getTransform()->getRotation();
	float f;

	// The modifier m_cAxis represents the axis the object will rotate around
	if (m_cAxis == 'x')
	{
		if(iDir > 0) f = v3Rot.x + m_fObjectRotateSpeed;
		else f = v3Rot.x - m_fObjectRotateSpeed;
		m_vTargetGameObjects[m_iTargetIndex]->getTransform()->setRotation(f, v3Rot.y, v3Rot.z);
	}

	if (m_cAxis == 'y')
	{
		if (iDir > 0) f = v3Rot.y + m_fObjectRotateSpeed;
		else f = v3Rot.y - m_fObjectRotateSpeed;
		m_vTargetGameObjects[m_iTargetIndex]->getTransform()->setRotation(v3Rot.x, f, v3Rot.z);
	}

	if (m_cAxis == 'z')
	{
		if (iDir > 0) f = v3Rot.z + m_fObjectRotateSpeed;
		else f = v3Rot.z - m_fObjectRotateSpeed;
		m_vTargetGameObjects[m_iTargetIndex]->getTransform()->setRotation(v3Rot.x, v3Rot.y, f);
	}
}

// Memory clean up
void BasicCameraController::Destroy()
{
	m_vTargetGameObjects.clear();
}

// Updates matrices for Projection and view using parents>transform>position
// Handles camera input events for movement and rotation
void BasicCameraController::update()
{	
	// Toggle Camera Position to the other view
	if (Input::getInput().getKeyboard()->isKeyDown(SDLK_F2))
	{
		toggleViewMode();
	}
	
	//Grab input
	if (Input::getInput().getKeyboard()->isKeyDown(SDLK_w))
	{
		if (m_bCanMove) moveCamera("forward");
	}
	else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_s))
	{
		if (m_bCanMove) moveCamera("backward");
	}

	if (Input::getInput().getKeyboard()->isKeyDown(SDLK_a))
	{
		rotateCameraHorizontal(-1);
	}
	else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_d))
	{
		rotateCameraHorizontal(1);
	}

	if (Input::getInput().getKeyboard()->isKeyDown(SDLK_CAPSLOCK))
	{
		setLookingAtTarget(!m_bLookAtTarget);
	}

	if (Input::getInput().getKeyboard()->isKeyDown(SDLK_TAB) && m_bLookAtTarget)
	{
		iterateThroughTargets();
	}

	if (Input::getInput().getKeyboard()->isKeyDown(SDLK_l) && m_bLookAtTarget)
	{
		;
		//promptInputForLight();
	}

	if (Input::getInput().getKeyboard()->isKeyDown(SDLK_F1))
	{
		std::cout << "CONTROLS: Press F1 for 'help' (command list)" << std::endl;
		std::cout << "NAVIGATION:" << std::endl;
		std::cout << "[W]: Move camera FORWARD" << std::endl;
		std::cout << "[S]: Move camera BACKWARD" << std::endl;
		std::cout << "[A]: Rotate camera LEFT" << std::endl;
		std::cout << "[D]: Rotate camera RIGHT" << std::endl;
		std::cout << "[SPACE]: Move camera UP" << std::endl;
		std::cout << "[LEFT_SHIFT]: Move camera DOWN" << std::endl;
		std::cout << "OBJECT MANIPULATION" << std::endl;
		std::cout << "[CAPS_LOCK]: Target scene objects " << std::endl;
		std::cout << "[TAB]: Iterate through scene objects" << std::endl;
		std::cout << "...while locked onto an object" << std::endl;
		std::cout << "[Q]: Rotate positively round an object " << std::endl;
		std::cout << "[E]: Rotate negatively round an object" << std::endl;
		std::cout << "Change Rotate Axis" << std::endl;
		std::cout << "[1]: round the x-axis " << std::endl;
		std::cout << "[2]: round the y-axis " << std::endl;
		std::cout << "[3]: round the z-axis" << std::endl;
		std::cout << "...To move objects" << std::endl;
		std::cout << "[UP_ARROW][DOWN_ARROW][LEFT_ARROW][RIGHT_ARROW]" << std::endl;
		std::cout << "[B]: LINE MODE " << std::endl;
		std::cout << "[N]: POINT MODE" << std::endl;
		std::cout << "[M]: FILL MODE" << std::endl;
	}

	//if locked onto a target
	if (m_bLookAtTarget)
	{
		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_UP)) moveObject("forward");
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_DOWN)) moveObject("backward");
		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_LEFT)) moveObject("left");
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_RIGHT)) moveObject("right");

		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_1)) m_cAxis = 'x';
		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_2)) m_cAxis = 'y';
		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_3)) m_cAxis = 'z';

		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_q)) rotateObject(1);
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_e)) rotateObject(-1);
	}
	
	//get the position from the transform
	vec3 v3CameraPosition = m_Parent->getTransform()->getPosition();

	m_m4Projection = glm::perspective(m_fFOV, m_fAspectRatio, m_fNearClip, m_fFarClip);
	
	//if looking at target
	if (m_bLookAtTarget)
	{
		vec3 v3LookPosition = m_vTargetGameObjects[m_iTargetIndex]->getTransform()->getPosition();
		m_m4View = glm::lookAt(v3CameraPosition, v3LookPosition, m_v3Up);
	}
	else m_m4View = glm::lookAt(v3CameraPosition, m_v3LookAt, m_v3Up); //not looking at target
}