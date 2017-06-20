#include "Enemy.h"

Enemy::Enemy() 
{
	m_bIsMoving = false;
}

Enemy::~Enemy()
{

}

void Enemy::update() 
{
	if (calculateDistanceToTarget() < m_fDistanceToEngage) m_bIsMoving = true;
	else m_bIsMoving = false;

	if (m_bIsMoving)
	{
		calculateDirectionToMove();
		move();
	}
}
float Enemy::calculateDistanceToTarget()
{
	float fResult;
	vec3 v3Go = m_gameObject->getTransform()->getPosition();
	vec3 v3Target = m_goTarget->getTransform()->getPosition();

	//P1P2 |= (sq root)(x2-x1)2 + (y2-y1)2 + (z2-z1)2

	return fResult = (v3Go.x - v3Target.x) * (v3Go.x - v3Target.x) +
		(v3Go.y - v3Target.y) * (v3Go.y - v3Target.y) +
		(v3Go.z - v3Target.z) * (v3Go.z - v3Target.z);
}
void Enemy::calculateDirectionToMove() 
{
	vec3 v3EnemyPosition = m_gameObject->getTransform()->getPosition();
	vec3 v3TargetPosition = m_goTarget->getTransform()->getPosition();
	float fX = v3EnemyPosition.x - v3TargetPosition.x;
	float fZ = v3EnemyPosition.z - v3TargetPosition.z;

	//Compare
	if (abs(fX) > abs(fZ))
	{
		if (fX > 0) m_iDirection = eMoveDirections::EAST;
		else m_iDirection = eMoveDirections::WEST;
	}
	else
	{
		if (fZ > 0) m_iDirection = eMoveDirections::NORTH;
		else m_iDirection = eMoveDirections::SOUTH;
	}
}

void Enemy::move() 
{
	Transform *t = m_gameObject->getTransform();	// Store transform for setting position
	vec3 v3Cur = t->getPosition();					// Stores step position for setting this enemies position

	switch (m_iDirection) 
	{
	case eMoveDirections::NORTH:
		v3Cur = v3Cur + vec3(0.0f,0.0f,-0.02f);
		t->setPosition(v3Cur.x, v3Cur.y, v3Cur.z);
		break;
	case eMoveDirections::EAST:
		v3Cur = v3Cur + vec3(-0.02f, 0.0f, 0.0f);
		t->setPosition(v3Cur.x, v3Cur.y, v3Cur.z);
		break;
	case eMoveDirections::SOUTH:
		v3Cur = v3Cur + vec3(0.0f, 0.0f, 0.02f);
		t->setPosition(v3Cur.x, v3Cur.y, v3Cur.z);
		break;
	case eMoveDirections::WEST:
		v3Cur = v3Cur + vec3(0.02f, 0.0f, 0.0f);
		t->setPosition(v3Cur.x, v3Cur.y, v3Cur.z);
		break;

	}
}