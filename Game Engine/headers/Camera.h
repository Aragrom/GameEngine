#ifndef Camera_h
#define Camera_h


#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"

class Camera:public Component
{
public:

    Camera();	// Constructor
    ~Camera();	// Deconstructor
    
	void update();
    
	//Setters
	void setLook(float x, float y, float z);	// Sets the camera LOOK AT property    
	void setUp(float x, float y, float z);		// Set Camera Up Vector property
    void setNearClip(float near);				// Set Camera Near Clip property
    void setFarClip(float far);					// Set Camera Far Clip property
	void setFOV(float FOV);						// Set Camera Field of View property
	void setAspectRatio(float ratio);			// Set Camera Aspect Ratio property
    
	// Getters
	mat4& getView();				// Get Camera VIEW MATRIX
	mat4& getProjection();			// Get Camera PROJECTION MATRIX
    vec3& getLookAt();				// Get Camera Look at vector-3
    vec3& getUp();					// Get Camera look up vector-3
    
    static vec3& calculateLookAtFromAngle(const vec3& rot);		// Calculate Look At angle return vector 3

protected:

	// Camera Properties
	float m_fNearClip;
	float m_fFarClip;
	float m_fFOV;
	float m_fAspectRatio;

	// View and Projection Matrix
	mat4 m_m4View;
	mat4 m_m4Projection;

	vec3 m_v3LookAt;				// Stores Look at Vector-3
	vec3 m_v3Up;					// Stores Up Vector-3
};

#endif
