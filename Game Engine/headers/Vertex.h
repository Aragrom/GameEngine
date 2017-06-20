#ifndef Vertex_h
#define Vertex_h

#include <glm/glm.hpp>
using glm::vec4;
using glm::vec3;
using glm::vec2;

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;
	vec4 colours;
	vec3 tangentNormals;
	vec3 binormals;
};

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#endif
