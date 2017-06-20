#include "FBXLoader.h"

#include "GameObject.h"

#include "Mesh.h"
#include "Transform.h"

#include <iostream>
#include "glm\vec3.hpp"

int level = 0; 

void PrintTabs() {
	for (int i = 0; i < level; i++)
		printf("\t");
}

/**
* Return a string-based representation based on the attribute type.
*/
FbxString GetAttributeTypeName(FbxNodeAttribute::EType type) {
	switch (type) {
	case FbxNodeAttribute::eUnknown: return "unidentified";
	case FbxNodeAttribute::eNull: return "null";
	case FbxNodeAttribute::eMarker: return "marker";
	case FbxNodeAttribute::eSkeleton: return "skeleton";
	case FbxNodeAttribute::eMesh: return "mesh";
	case FbxNodeAttribute::eNurbs: return "nurbs";
	case FbxNodeAttribute::ePatch: return "patch";
	case FbxNodeAttribute::eCamera: return "camera";
	case FbxNodeAttribute::eCameraStereo: return "stereo";
	case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
	case FbxNodeAttribute::eLight: return "light";
	case FbxNodeAttribute::eOpticalReference: return "optical reference";
	case FbxNodeAttribute::eOpticalMarker: return "marker";
	case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
	case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
	case FbxNodeAttribute::eBoundary: return "boundary";
	case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
	case FbxNodeAttribute::eShape: return "shape";
	case FbxNodeAttribute::eLODGroup: return "lodgroup";
	case FbxNodeAttribute::eSubDiv: return "subdiv";
	default: return "unknown";
	}
}

GameObject * loadFBXFromFile(const std::string& filename, vec3 v3ObjectScale)
{
	GameObject *rootGo = NULL;
	level = 0;
	// Initialize the SDK manager. This object handles memory management.
	FbxManager* lSdkManager = FbxManager::Create();

	// Create the IO settings object.
	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	// Create an importer using the SDK manager.
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

	// Create a new scene so that it can be populated by the imported file.
	if (!lImporter->Initialize(filename.c_str(), -1, lSdkManager->GetIOSettings())) 
	{
		return rootGo;
	}

	// Create a new scene so that it can be populated by the imported file.
	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
	// Import the contents of the file into the scene.
	lImporter->Import(lScene);

	// Print the nodes of the scene and their attributes recursively.
	// Note that we are not printing the root node because it should
	// not contain any attributes.
	FbxNode* lRootNode = lScene->GetRootNode();
	if (lRootNode) {
		rootGo = new GameObject();
		rootGo->setTransform(new Transform());

		std::cout << "Root Node " << lRootNode->GetName() << std::endl;
		for (int i = 0; i < lRootNode->GetChildCount(); i++)
		{
			processNode(lRootNode->GetChild(i), rootGo, v3ObjectScale);
		}
	}

	return rootGo;
}

void processNode(FbxNode *node,GameObject *rootGo, vec3 v3ObjectScale)
{
	PrintTabs();
	const char* nodeName = node->GetName();
	FbxDouble3 translation =  node->LclTranslation.Get();
	FbxDouble3 rotation = node->LclRotation.Get();
	FbxDouble3 scaling = node->LclScaling.Get();

	std::cout << "Node " << nodeName << " Postion " << translation[0] << " " << translation[1] << " " << translation[2] << " "
		<< " Rotation " << rotation[0] << " " << rotation[1] << " " << rotation[2] << " "
		<< " Scale " << scaling[0] << " " << scaling[1] << " " << scaling[2] << std::endl;

	level++;
	GameObject * go = new GameObject();
	go->setTransform(new Transform());
	rootGo->addChild(go);

	// Print the node's attributes.
	for (int i = 0; i < node->GetNodeAttributeCount(); i++){
		processAttribute(node->GetNodeAttributeByIndex(i), go, v3ObjectScale);
	}

	// Recursively print the children.
	for (int j = 0; j < node->GetChildCount(); j++)
		processNode(node->GetChild(j), rootGo, v3ObjectScale);
	level--;
	PrintTabs();
}

void processAttribute(FbxNodeAttribute * attribute, GameObject * go, vec3 v3ObjectScale)
{
	if (!attribute) return;
	FbxString typeName = GetAttributeTypeName(attribute->GetAttributeType());
	FbxString attrName = attribute->GetName();
	PrintTabs();
	std::cout << "Attribute " << typeName.Buffer() << " Name " << attrName << std::endl;
	switch (attribute->GetAttributeType()) {
	case FbxNodeAttribute::eSkeleton: return;
	case FbxNodeAttribute::eMesh: processMesh(attribute->GetNode()->GetMesh(),go, v3ObjectScale);
	case FbxNodeAttribute::eCamera: return;
	case FbxNodeAttribute::eLight: return;
	}
}

void processMesh(FbxMesh * mesh, GameObject *go, vec3 v3ObjectScale)
{
	Mesh * meshComponent = new Mesh();
	meshComponent->init();

	int numIndices = mesh->GetPolygonVertexCount();
	int numVerts = mesh->GetControlPointsCount();

	int *pIndices = mesh->GetPolygonVertices();
	Vertex * pVerts = new Vertex[numVerts];

	for (int i = 0; i < numVerts; i++)
	{
		FbxVector4 currentVert = mesh->GetControlPointAt(i);

		//if (strObjectType =)
		//{
		pVerts[i].position = vec3(currentVert[0] / v3ObjectScale.x, currentVert[1] / v3ObjectScale.y, currentVert[2] / v3ObjectScale.z);

		//}
		pVerts[i].colours = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		pVerts[i].texCoords = vec2(0.0f, 0.0f);
		pVerts[i].binormals = vec3(0.0f, 0.0f, 0.0f);
		pVerts[i].tangentNormals = vec3(0.0f, 0.0f, 0.0f);
	}

	//read normal
	processMeshNormals(mesh, pVerts, numVerts);
	processMeshTextureCoords(mesh, pVerts, numVerts); 

	//read texture coordinates
	std::cout << "Vertices " << numVerts << " Indices " << numIndices << std::endl;

	calculateTagentAndBinormals(pVerts, numVerts, pIndices, numIndices);

	meshComponent->copyIndexData(numIndices, sizeof(int), (void**)pIndices);
	meshComponent->copyVertexData(numVerts, sizeof(Vertex), (void**)pVerts);

	go->setMesh(meshComponent);
	if (pVerts)
	{
		delete[] pVerts;
		pVerts = NULL;
	}
}

void processMeshNormals(FbxMesh * mesh, Vertex * verts, int numVerts)
{
	for (int iPolygon = 0; iPolygon < mesh->GetPolygonCount(); iPolygon++) {
		for (unsigned iPolygonVertex = 0; iPolygonVertex < 3; iPolygonVertex++) {
			int fbxCornerIndex = mesh->GetPolygonVertex(iPolygon, iPolygonVertex);
			FbxVector4 fbxNormal;
			mesh->GetPolygonVertexNormal(iPolygon, iPolygonVertex, fbxNormal);
			fbxNormal.Normalize();
			verts[fbxCornerIndex].normal.x = fbxNormal[0];
			verts[fbxCornerIndex].normal.y = fbxNormal[1];
			verts[fbxCornerIndex].normal.z = fbxNormal[2];
		}
	}
}

void processMeshTextureCoords(FbxMesh * mesh, Vertex * verts, int numVerts)
{
	for (int iPolygon = 0; iPolygon < mesh->GetPolygonCount(); iPolygon++) {
		for (unsigned iPolygonVertex = 0; iPolygonVertex < 3; iPolygonVertex++) {
			int fbxCornerIndex = mesh->GetPolygonVertex(iPolygon, iPolygonVertex);
			FbxVector2 fbxUV = FbxVector2(0.0, 0.0);
			FbxLayerElementUV* fbxLayerUV = mesh->GetLayer(0)->GetUVs();
			// Get texture coordinate	
			if (fbxLayerUV) {
				int iUVIndex = 0;
				switch (fbxLayerUV->GetMappingMode()) {
				case FbxLayerElement::eByControlPoint:
					iUVIndex = fbxCornerIndex;
					break;
				case FbxLayerElement::eByPolygonVertex:
					iUVIndex = mesh->GetTextureUVIndex(iPolygon, iPolygonVertex, FbxLayerElement::eTextureDiffuse);
					break;
				}
				fbxUV = fbxLayerUV->GetDirectArray().GetAt(iUVIndex);
				verts[fbxCornerIndex].texCoords.x = fbxUV[0];
				verts[fbxCornerIndex].texCoords.y = 1.0f - fbxUV[1];
			}
		}
	}
}

//Bug in some exporters means that we will have to calculate these!
void calculateTagentAndBinormals(Vertex * verts, int numVerts, int * indices, int numIndices)
{
	//create arrays for 
	for (int i = 0; i < numIndices; i += 3)
	{
		vec3 vertex0 = verts[indices[i]].position;
		vec3 vertex1 = verts[indices[i+1]].position;
		vec3 vertex2 = verts[indices[i+2]].position;

		vec3 normal = glm::cross((vertex1 - vertex0), (vertex2 - vertex0));

		vec3 deltaPos;
		if (vertex0 == vertex1)
			deltaPos = vertex2 - vertex0;
		else
			deltaPos = vertex1 - vertex0;

		vec2 uv0 = verts[indices[i]].texCoords;
		vec2 uv1 = verts[indices[i+1]].texCoords;
		vec2 uv2 = verts[indices[i+2]].texCoords;

		vec2 deltaUV1 = uv1 - uv0;
		vec2 deltaUV2 = uv2 - uv0;

		vec3 tan; // tangents
		vec3 bin; // binormal

		// avoid divion with 0
		if (deltaUV1.s != 0)
			tan = deltaPos / deltaUV1.s;
		else
			tan = deltaPos / 1.0f;

		tan = glm::normalize(tan - glm::dot(normal, tan)*normal);

		bin = glm::normalize(glm::cross(tan, normal));

		verts[indices[i]].tangentNormals=tan;
		verts[indices[i + 1]].tangentNormals = tan;
		verts[indices[i + 2]].tangentNormals = tan;

		verts[indices[i]].binormals = bin;
		verts[indices[i + 1]].binormals = bin;
		verts[indices[i + 2]].binormals = bin;
	}
}