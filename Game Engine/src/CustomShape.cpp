#include "GameObject.h"

#include "CustomShape.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

#include "Vertex.h"

CustomShape::CustomShape()
{
	
}

void CustomShape::generateMesh(GameObject * go, GLuint indices[], Vertex vertices[], int iIndices, int iVertices)
{
	Mesh * meshComponent = new Mesh();
	meshComponent->init();

	meshComponent->copyVertexData(iVertices, sizeof(Vertex), (void**)vertices);
	meshComponent->copyIndexData(iIndices, sizeof(int), (void**)indices);

	go->setMesh(meshComponent);
}

void CustomShape::init(GameObject * go)
{
	Mesh * meshComponent = new Mesh();
	meshComponent->init();

	const int i = 8;
	Vertex vertices[i];

	vertices[0].position = vec3(-1.0f, 1.0f, 1.0f);
	vertices[0].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[0].normal = vec3(0.0f, 0.0f, 0.0f);
	vertices[0].texCoords = vec2(0.0f, 0.0f);
	vertices[0].binormals = vec3(-1.0f, 0.0f, 0.0f);
	vertices[0].tangentNormals = vec3(0.0f, 0.0f, 0.0f);

	vertices[1].position = vec3(-1.0f, -1.0f, 1.0f);
	vertices[1].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[1].normal = vec3(0.0f, 0.0f, 0.0f);
	vertices[1].texCoords = vec2(0.0f, 0.0f);
	vertices[1].binormals = vec3(0.0f, 0.0f, 0.0f);
	vertices[1].tangentNormals = vec3(0.0f, 0.0f, 0.0f);

	vertices[2].position = vec3(1.0f, -1.0f, 1.0f);
	vertices[2].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[2].normal = vec3(0.0f, 0.0f, 0.0f);
	vertices[2].texCoords = vec2(0.0f, 0.0f);
	vertices[2].binormals = vec3(0.0f, 0.0f, 0.0f);
	vertices[2].tangentNormals = vec3(0.0f, 0.0f, 0.0f);

	vertices[3].position = vec3(1.0f, 1.0f, 1.0f);
	vertices[3].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[3].normal = vec3(0.0f, 0.0f, 0.0f);
	vertices[3].texCoords = vec2(0.0f, 0.0f);
	vertices[3].binormals = vec3(0.0f, 0.0f, 0.0f);
	vertices[3].tangentNormals = vec3(0.0f, 0.0f, 0.0f);

	vertices[4].position = vec3(-1.0f, 1.0f, -1.0f);
	vertices[4].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[4].normal = vec3(0.0f, 0.0f, 0.0f);
	vertices[4].texCoords = vec2(0.0f, 0.0f);
	vertices[4].binormals = vec3(0.0f, 0.0f, 0.0f);
	vertices[4].tangentNormals = vec3(0.0f, 0.0f, 0.0f);

	vertices[5].position = vec3(-1.0f, -1.0f, -1.0f);
	vertices[5].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[5].normal = vec3(0.0f, 0.0f, 0.0f);
	vertices[5].texCoords = vec2(0.0f, 0.0f);
	vertices[5].binormals = vec3(0.0f, 0.0f, 0.0f);
	vertices[5].tangentNormals = vec3(0.0f, 0.0f, 0.0f);

	vertices[6].position = vec3(1.0, -1.0f, -1.0f);
	vertices[6].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[6].normal = vec3(0.0f, 0.0f, 0.0f);
	vertices[6].texCoords = vec2(0.0f, 0.0f);
	vertices[6].binormals = vec3(0.0f, 0.0f, 0.0f);
	vertices[6].tangentNormals = vec3(0.0f, 0.0f, 0.0f);

	vertices[7].position = vec3(1.0f, 1.0f, -1.0f);
	vertices[7].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[7].normal = vec3(0.0f, 0.0f, 0.0f);
	vertices[7].texCoords = vec2(0.0f, 0.0f);
	vertices[7].binormals = vec3(0.0f, 0.0f, 0.0f);
	vertices[7].tangentNormals = vec3(0.0f, 0.0f, 0.0f);

	meshComponent->copyVertexData(8, sizeof(Vertex), (void**)vertices);

	GLuint indices[] = { 0, 2, 3, 0, 1, 2,
						4, 6, 7, 4, 5, 6,
						0, 4, 1, 4, 5, 1,
						2, 6, 3, 6, 7, 3,
						6, 1, 5, 6, 2, 1,
						0, 7, 4, 0, 3, 7 };
	meshComponent->copyIndexData(36, sizeof(int), (void**)indices);

	go->setMesh(meshComponent);
}

void CustomShape::sprite(GameObject * go)
{
	Mesh * meshComponent = new Mesh();
	meshComponent->init();

	Vertex spriteVertices[4];
	float fWidth = 300.0f;
	float fHeight = 300.0f;

	spriteVertices[0].position = vec3(0.0, 0.0f, 0.0f);
	spriteVertices[0].texCoords = vec2(0.0f, 0.0f);
	spriteVertices[0].normal = vec3(0.0f, 0.0f, 1.0f);
	spriteVertices[0].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);// Top Left
	spriteVertices[0].binormals = vec3(0.0f, -1.0f, 0.0f);
	spriteVertices[0].tangentNormals = vec3(0.0f, -1.0f, 0.0f);

	spriteVertices[1].position = vec3(0.0f, fHeight, 0.0f);
	spriteVertices[1].texCoords = vec2(0.0f, 1.0f);
	spriteVertices[1].normal = vec3(0.0f, 0.0f, 1.0f);
	spriteVertices[1].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);//Bottom Left
	spriteVertices[1].binormals = vec3(0.0f, -1.0f, 0.0f);
	spriteVertices[1].tangentNormals = vec3(0.0f, -1.0f, 0.0f);

	spriteVertices[2].position = vec3(fWidth, fHeight, 0.0f);
	spriteVertices[2].texCoords = vec2(1.0f, 1.0f);
	spriteVertices[2].normal = vec3(0.0f, 0.0f, 1.0f);
	spriteVertices[2].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);//Bottom Right
	spriteVertices[2].binormals = vec3(0.0f, -1.0f, 0.0f);
	spriteVertices[2].tangentNormals = vec3(0.0f, -1.0f, 0.0f);

	spriteVertices[3].position = vec3(fWidth, 0.0f, 0.0f);
	spriteVertices[3].texCoords = vec2(1.0f, 0.0f);
	spriteVertices[3].normal = vec3(0.0f, 0.0f, 1.0f);
	spriteVertices[3].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f); //Top	Right
	spriteVertices[3].binormals = vec3(0.0f, -1.0f, 0.0f);
	spriteVertices[3].tangentNormals = vec3(0.0f, -1.0f, 0.0f);

	GLuint spriteIndices[] = { 0,1,2,0,3,2, };

	meshComponent->copyVertexData(8, sizeof(Vertex), (void**)spriteVertices);
	meshComponent->copyIndexData(36, sizeof(int), (void**)spriteIndices);

	go->setMesh(meshComponent);
}