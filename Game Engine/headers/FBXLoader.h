#ifndef FBXLoader_H
#define FBXLoader_H

#include <fbxsdk.h>
#include <string>
#include "Vertex.h"
#include "glm\vec3.hpp"

class GameObject;

GameObject * loadFBXFromFile(const std::string& filename, vec3 v3ObjectScale);
void processNode(FbxNode *node, GameObject *rootGo, vec3 v3ObjectScale);
void processAttribute(FbxNodeAttribute * attribute, GameObject * go, vec3 v3ObjectScale);
void processMesh(FbxMesh * mesh, GameObject *go, vec3 v3ObjectScale);
void processMeshNormals(FbxMesh * mesh, Vertex * verts, int numVerts);
void processMeshTextureCoords(FbxMesh * mesh, Vertex * verts, int numVerts);
void calculateTagentAndBinormals(Vertex * verts, int numVerts, int * indices, int numIndices);

#endif