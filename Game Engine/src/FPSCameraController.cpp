#include <iostream>

#include "FPSCameraController.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Timer.h"
#include "Input.h"

#include <glm/glm.hpp>
using glm::vec3;

#include <vector>

FPSCameraController::FPSCameraController()
{
	m_iIndex = 0;
	m_bViewLocked = false;
	m_camAttachedCamera = NULL;
    m_fForwardSpeed=100;
    m_fStrafeSpeed=80;
    m_fLookSpeed=1;
    m_Type="FPSCameraController";
    m_Name=m_Type;
}

FPSCameraController::~FPSCameraController()
{
    
}

void FPSCameraController::update()
{
    if (m_camAttachedCamera)
    {
		if (!m_bViewLocked)
		{
			//lets just use standard FPS Controllers(mouse & keyboard)
			vec3 currentPos = m_camAttachedCamera->getParent()->getTransform()->getPosition();
			vec3 currentRot = m_camAttachedCamera->getParent()->getTransform()->getRotation();
			vec3 currentLook = m_camAttachedCamera->getLookAt();
			//get a forward vector
			vec3 forward = currentLook - currentPos;
			forward.y = 0.0f;
			forward = glm::normalize(forward);

			//calculate a right vector
			vec3 right = glm::cross(m_camAttachedCamera->getUp(), forward);
			right = glm::normalize(right);

			//Grab input
			if (Input::getInput().getKeyboard()->isKeyDown(SDLK_w))
			{
				currentPos.z += forward.z*m_fForwardSpeed*Timer::getTimer().getDeltaTime();
				currentLook.z += forward.z*m_fForwardSpeed*Timer::getTimer().getDeltaTime();
			}
			else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_s))
			{
				currentPos.z -= forward.z*m_fForwardSpeed*Timer::getTimer().getDeltaTime();
				currentLook.z -= forward.z*m_fForwardSpeed*Timer::getTimer().getDeltaTime();
			}

			if (Input::getInput().getKeyboard()->isKeyDown(SDLK_a))
			{
				currentPos += right*m_fStrafeSpeed*Timer::getTimer().getDeltaTime();
				currentLook += right*m_fStrafeSpeed*Timer::getTimer().getDeltaTime();
			}
			else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_d))
			{
				currentPos += right*(m_fStrafeSpeed*-1)*Timer::getTimer().getDeltaTime();
				currentLook += right*(m_fStrafeSpeed*-1)*Timer::getTimer().getDeltaTime();
			}

			//get the mouse values and directly move the yaw & pitch of the camera(the x and y of the camera rotation)

			//use these to caculate the look at
			int mouseX = Input::getInput().getMouse()->getRelativeMouseX();
			int mouseY = Input::getInput().getMouse()->getRelativeMouseY();

			currentRot.y += mouseX*Timer::getTimer().getDeltaTime()*m_fLookSpeed;
			currentRot.x += mouseY*Timer::getTimer().getDeltaTime()*m_fLookSpeed;

			//adjust values
			m_camAttachedCamera->getParent()->getTransform()->setRotation(currentRot.x, currentRot.y, currentRot.z);
			m_camAttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
			m_camAttachedCamera->setLook(currentLook.x + (cos(currentRot.x)*cos(currentRot.y)),
				currentLook.y,
				currentLook.z + (sin(currentRot.x)*cos(currentRot.y)));
		}

		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_CAPSLOCK))
		{
			m_iIndex = 0;

			LookAtTarget(m_iIndex);

			if (m_bViewLocked)
			{
				m_bViewLocked = false;
				std::cout << "!!! - View UNLOCKED - !!!" << std::endl;
				m_Parent->getCamera()->setLook(m_v3LastLookedPosition.x, m_v3LastLookedPosition.y, m_v3LastLookedPosition.z);
			}
			else
			{
				m_bViewLocked = true;
				std::cout << "!!! - View LOCKED - !!!" << std::endl;
				m_v3LastLookedPosition = m_Parent->getCamera()->getLookAt();
			}
		}

		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_TAB) && m_bViewLocked)
		{
			if (m_iIndex < m_vLookAtTargets.size() - 1) m_iIndex++;
			else m_iIndex = 0;

			LookAtTarget(m_iIndex);
			std::cout << "!!! - Iterated through GameObjects - !!!" << std::endl;
		}
    }
}

void FPSCameraController::setCamera(Camera * cam)
{
    m_camAttachedCamera=cam;
}

void FPSCameraController::addGameObjectToTargets(GameObject *go)
{
	m_vLookAtTargets.push_back(go);
}

void FPSCameraController::LookAtTarget(int iIndex)
{
	vec3 v3LookAt = m_vLookAtTargets[iIndex]->getTransform()->getPosition();

	m_camAttachedCamera->setLook(v3LookAt.x, v3LookAt.y, v3LookAt.z);
}
