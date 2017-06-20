#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

Camera::Camera()
{
	m_Type = "Camera";
	m_v3LookAt=vec3(0.0f,0.0f,0.0f);
	m_v3Up=vec3(0.0f,1.0f,0.0f);
	m_fNearClip=0.1f;
	m_fFarClip = 100.0f;
	m_fFOV=45.0f;
	m_fAspectRatio=16.0f/9.0f;
	m_m4View = mat4();
	m_m4Projection = mat4();
}

Camera::~Camera()
{

}

void Camera::update()
{
	//get the position from the transform
	vec3 position = m_Parent->getTransform()->getPosition();
    
	m_m4Projection = glm::perspective(m_fFOV, m_fAspectRatio, m_fNearClip, m_fFarClip);
	m_m4View = glm::lookAt(position, m_v3LookAt, m_v3Up);
}

void Camera::setLook(float x, float y, float z)
{
    m_v3LookAt = vec3(x, y, z);
}

void Camera::setUp(float x, float y, float z)
{
    m_v3Up = vec3(x, y, z);
}


 void Camera::setNearClip(float near)
 {
     m_fNearClip = near;
 }
 
 void Camera::setFarClip(float far)
 {
     m_fFarClip = far;
 }

void Camera::setFOV(float FOV)
{
    m_fFOV = FOV;
}

void Camera::setAspectRatio(float ratio)
{
    m_fAspectRatio = ratio;
}

mat4& Camera::getView()
{
    return m_m4View;
}

mat4& Camera::getProjection()
{
    return m_m4Projection;
}

vec3& Camera::getLookAt()
{
    return m_v3LookAt;
}

vec3& Camera::getUp()
{
    return m_v3Up;
}

vec3& Camera::calculateLookAtFromAngle(const vec3& rot)
{
    vec3 lookAt=vec3(1.0f,1.0f,1.0f);
    
    lookAt.x=(cos(rot.x)*cos(rot.y));
    lookAt.y=(sin(rot.y));
    lookAt.z=(sin(rot.x)*cos(rot.y));
    
    return lookAt;
}