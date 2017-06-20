#ifndef BoxCollider_h
#define BoxCollider_h

#include "GameConstants.h"

class BoxCollider : public Collider
{
public:

	//Getters
	float getLength() { return m_fLength; }
	float getWidth() { return m_fWidth; }
	float getHeight() { return m_fHeight; }
	std::vector<vec3*> getColliderVertices() { return m_colliderVertices; }

	//Setters
	void setLength(float x) { m_fLength = x; }
	void setHeight(float y) { m_fHeight = y; }
	void setWidth(float z) { m_fWidth = z; }

	BoxCollider(float fWidth, float fHeight, float fLength); //Constructor
	~BoxCollider();	// Deconstructor

	void createColliderVertices();							// Creates vertices based on Transform Components Position (as a center)
	bool withinColliderCheckPointer(vec3 *pos);				// Check pointer for vector 3 in Box Collider's boundings
	bool withinColliderCheck(vec3 pos);						// Check for vector 3 in Box Collider's boundings
	bool withinColliderCheck(BoxCollider *boxCollider);		// Takes a Box Collider, Using its vertices checks each one within the Box Collider's Boundings

private:

	std::vector<vec3*> m_colliderVertices;		// Holds vertices for Box Collider
	float m_fLength;							// Length of Box
	float m_fWidth;								// Width of Box
	float m_fHeight;							// Height of Box
};
#endif
