#include "GameConstants.h"

#include "SphereCollider.h"

//Getters
float SphereCollider::getRadius() { return m_fRadius; }

//Setters
void SphereCollider::setRadius(float fRadius) { m_fRadius = fRadius; }

SphereCollider::SphereCollider(float fRadius)
{
	m_Active = true;
	m_Type = "Collider";
	setColliderType("SphereCollider");
	m_fRadius = fRadius;
}

bool SphereCollider::withinColliderCheckPointer(vec3 *pos)
{
	vec3 v3Center = m_Parent->getTransform()->getPosition();

	//P1P2 |= (sq root)(x2-x1)2 + (y2-y1)2 + (z2-z1)2

	float fDistance = (pos->x - v3Center.x) * (pos->x - v3Center.x) +
		(pos->y - v3Center.y) * (pos->y - v3Center.y) +
		(pos->z - v3Center.z) * (pos->z - v3Center.z);

	if (std::abs(fDistance) < m_fRadius) return true;
	else return false;
}
bool SphereCollider::withinColliderCheck(vec3 pos) 
{
	vec3 v3Center = m_Parent->getTransform()->getPosition();
	float fDistance = (pos.x - v3Center.x) * (pos.x - v3Center.x) +
		(pos.y - v3Center.y) * (pos.y - v3Center.y) +
		(pos.z - v3Center.z) * (pos.z - v3Center.z);

	if (std::abs(fDistance) < m_fRadius) return true;
	else return false;
}
bool SphereCollider::withinColliderCheck(SphereCollider sphereCollider) 
{
	vec3 v3Center = m_Parent->getTransform()->getPosition();
	vec3 v3OtherCenter = sphereCollider.getParent()->getTransform()->getPosition();
	float fDistance = (v3OtherCenter.x - v3Center.x) * (v3OtherCenter.x - v3Center.x) +
		(v3OtherCenter.y - v3Center.y) * (v3OtherCenter.y - v3Center.y) +
		(v3OtherCenter.z - v3Center.z) * (v3OtherCenter.z - v3Center.z);

	float fCombinedRadius = m_fRadius + sphereCollider.getRadius();
	if (std::abs(fDistance) < fCombinedRadius) return true;
	else return false;
}