#ifndef FPSCameraController_h
#define FPSCameraController_h

#include "Component.h"
#include <glm/glm.hpp>
using glm::vec3;
#include <vector>

class Camera;

class FPSCameraController : public Component
{
public:

	// Setters
	void setCamera(Camera * camCam);
	void setSpeed(float fSpeed);

    FPSCameraController();	// Constructor
    ~FPSCameraController();	// Deconstructor
    
	void update();

	void addGameObjectToTargets(GameObject *go);

	void LookAtTarget(int iIndex);

private:

	bool m_bViewLocked;
	int m_iIndex;

    float m_fForwardSpeed;
    float m_fStrafeSpeed;
    float m_fLookSpeed;
    Camera * m_camAttachedCamera;
	std::vector<GameObject*> m_vLookAtTargets;
	vec3 m_v3LastLookedPosition;
};


#endif
