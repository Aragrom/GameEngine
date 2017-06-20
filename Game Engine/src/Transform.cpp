#include "Transform.h"
#include "GameObject.h"

Transform::Transform()
{
    m_Position=vec3(0.0f,0.0f,0.0f);
    m_Rotation=vec3(0.0f,0.0f,0.0f);
    m_Scale=vec3(1.0f,1.0f,1.0f);
    m_Model=mat4();
}

Transform::~Transform()
{
    
}

void Transform::update()
{
	mat4 translate = glm::translate(mat4(1.0f), m_Position);
	mat4 scale = glm::scale(mat4(1.0f), m_Scale);
    
	mat4 rotationX = glm::rotate(mat4(1.0f), m_Rotation.x, vec3(1.0f, 0.0f, 0.0f));
	mat4 rotationY = glm::rotate(mat4(1.0f), m_Rotation.y, vec3(0.0f, 1.0f, 0.0f));
	mat4 rotationZ = glm::rotate(mat4(1.0f), m_Rotation.z, vec3(0.0f, 0.0f, 1.0f));
	mat4 rotation = rotationX*rotationY*rotationZ;
    
	m_Model = translate*rotation*scale;
	if (m_Parent->getParent())
	{
		m_Model = m_Parent->getParent()->getTransform()->getModel()*m_Model;
	}
    
}

void Transform::setPosition(float x,float y,float z)
{
    m_Position=vec3(x,y,z);
}

void Transform::setRotation(float x,float y,float z)
{
    m_Rotation=vec3(x,y,z);
}

void Transform::setScale(float x,float y,float z)
{
    m_Scale=vec3(x,y,z);
}

vec3& Transform::getPosition()
{
    return m_Position;
}

vec3& Transform::getScale()
{
    return m_Scale;
}

vec3& Transform::getRotation()
{
    return m_Rotation;
}

mat4& Transform::getModel()
{
    return m_Model;
}