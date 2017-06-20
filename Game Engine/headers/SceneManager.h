#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "GameConstants.h"
#include "Enemy.h"
#include "Player.h"
#include "Planet.h"

class Enemy;
class Player;
class Planet;

class SceneManager
{
public:

	// Getters
	std::vector<GameObject*> SceneManager::getGameObjects() { return gameObjects; }
	GameObject* SceneManager::getMainCamera() { return goMainCamera; }
	GameObject* SceneManager::getMainLight() { return goMainLight; }
	Player* SceneManager::getPlayer() { return player; }

	void cleanUp();
	void initScene();
	bool update();

	void incrementBuildPosition();
	void rotateBuildDirection();
	void instantiateSun(vec3 v3InstantiatePosition);
	void instantiateEnemyBarrel(vec3 v3InstantiatePosition);
	void instantiateCustomShape(vec3 v3InstantiatePosition);
	void instantiateBlackHole(vec3 v3InstantiatePosition);
	void instantiateFloorSegment(vec3 v3InstantiatePosition);
	void instantiatePlanet(vec3 v3InstantiatePosition, float fDistanceToOrbit, float fOrbitSpeed);
	void instantiateVehicle(vec3 v3InstantiatePosition, float fDistanceToOrbit, float fOrbitSpeed);
	void createSkyBox();

	GameObject * skyBox = NULL;

private:

	BasicCameraController *basicCameraController;

	std::string vsPath;				// Holds string for Vertex Shader address
	std::string fsPath;				// Holds string for Fragment Shader address

	std::string modelPath;
	std::string texturePath;
	std::string heightMap;
	std::string specularMap;

	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> floorTiles;
	std::vector<Enemy*> enemies;
	std::vector<Planet*> planets;
	Player *player;
	GameObject * goHealth;
	GameObject * goMainCamera;
	GameObject * goMainLight;

	int iLevelSize;
	int iBuildDirection;
	vec3 v3BuildPosition;

	int iAmountOfStars;
};
#endif
