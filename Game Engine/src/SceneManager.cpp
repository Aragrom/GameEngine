#include "SceneManager.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

bool SceneManager::update() 
{
	bool bPlayHitSound = false;

	//==============================================================================
	// UPDATE SCENE RELATED OBJECTS
	//==============================================================================

	if (skyBox) skyBox->update();													// if SKYBOX exists UPDATE
	player->update();																// UPDATE PLAYER for falling and damage handling
	for (auto iter = planets.begin(); iter != planets.end(); iter++)				// for each PLANET call UPDATE
	{
		(*iter)->update();		// Rotates and transforms planets
	}
	for (auto iter = enemies.begin(); iter != enemies.end(); iter++)				// for each ENEMY 'BARREL' call UPDATE
	{
		(*iter)->update();		// Checks distance and then moves
	}

	//==============================================================================
	// Check JUST BELOW PLAYER for collision with GROUND - COLLISION DETECTION
	//==============================================================================
	vec3 v3PlayerPos = player->getGameObject()->getTransform()->getPosition();
	v3PlayerPos = v3PlayerPos + vec3(0.0f, -0.5f, 0.0f);							// Adjust position to check just below player
	bool bOnGround = false;															// if above any collider dont fall

	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
	{
		std::string strColliderType = std::string("");
		//Store collider type
		if ((*iter)->getCollider() != NULL) strColliderType = (*iter)->getCollider()->getColliderType();

		//if the collider type is BOX COLLIDER (no sphere colliders are used for supporting player)
		if (strColliderType == "BoxCollider")
		{
			BoxCollider *boxCollider = static_cast<BoxCollider*>((*iter)->getCollider());
			if(boxCollider->withinColliderCheck(v3PlayerPos)) bOnGround = true;
		}
	}

	player->setIsFalling(!bOnGround);												// set if falling
	BasicCameraController *basicCameraController = 
		static_cast<BasicCameraController*>(player->getGameObject()->getCamera());	// set if camera is falling
	basicCameraController->setCanMove(bOnGround);									// Based on result set camera property

	//==============================================================================
	// Check for Player within GameObjects colliders - COLLISION DETECTION
	//==============================================================================

	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
	{
		if ((*iter)->getCollider() != NULL)
		{
			//if you have 2 lives again game must be reset so reset all colliders with active state = false
			if (player->getPlayerHealth() == 2 && !(*iter)->getCollider()->isActive())
			{
				(*iter)->getCollider()->toggleActive();
				std::cout << "Toggled collider on reset" << std::endl;
			}
		}

		vec3 v3PlayerPos = goMainCamera->getTransform()->getPosition();
		bool bPlayerCollision;

		std::string strColliderType = std::string("");
		//Store collider type
		if((*iter)->getCollider() != NULL) strColliderType = (*iter)->getCollider()->getColliderType();
		bool bResult;

		//if the collider type is BOX COLLIDER
		if (strColliderType == "BoxCollider" && (*iter)->getCollider()->isActive())
		{
			BoxCollider *boxCollider = static_cast<BoxCollider*>((*iter)->getCollider());
			bResult = boxCollider->withinColliderCheck(v3PlayerPos);

			if (bResult)
			{
				if((*iter)->getName() != "BlackHole")
				{
					bPlayHitSound = true;	// Set to play audio on returning bool on update()

					std::cout << "Player collided with Box Collider on " << boxCollider->getParent()->getName() << " at position ("
						<< v3PlayerPos.x << ","
						<< v3PlayerPos.y << ","
						<< v3PlayerPos.z << ")"
						<< std::endl;

					if (player->takeDamage(1)) 
					{
						player->getGameObject()->getTransform()->setPosition(V3_START_POSITION.x, 300.0f, V3_START_POSITION.z + 10.0f);

						BasicCameraController *bsc = static_cast<BasicCameraController*>(player->getGameObject()->getCamera());
						bsc->setLookingAtTarget(true);
					} //dead
					else {} //still alive

					//(*iter)->getCollider()->setColliderType("");	// Disable collision happening again
					(*iter)->getCollider()->toggleActive();			// Disable collision happening again

					//Handle Collision (Current Primitive method)
					//int iDir = basicCameraController->getDir();
					//if (iDir > 0) basicCameraController->moveCamera("backward");
					//else basicCameraController->moveCamera("forward"); 
				}
				else // COMPLETED LEVEL 
				{
					player->getGameObject()->getTransform()->setPosition(V3_START_POSITION.x, 300.0f, V3_START_POSITION.z + 10.0f);

					BasicCameraController *bsc = static_cast<BasicCameraController*>(player->getGameObject()->getCamera());
					bsc->setLookingAtTarget(true);				// Set to play audio on returning bool on update()
				}
			}
		}

		//if the collider type is SPHERE COLLIDER
		if (strColliderType == "SphereCollider" && (*iter)->getCollider()->isActive())
		{
			SphereCollider *sphereCollider = static_cast<SphereCollider*>((*iter)->getCollider());
			bResult = sphereCollider->withinColliderCheck(v3PlayerPos);

			if (bResult)
			{
				if ((*iter)->getName() != "BlackHole")
				{
					bPlayHitSound = true;				// Set to play audio on returning bool on update()

					std::cout << "Player collided with Sphere Collider on " << sphereCollider->getParent()->getName() << " at position ("
						<< v3PlayerPos.x << ","
						<< v3PlayerPos.y << ","
						<< v3PlayerPos.z << ")"
						<< std::endl;

					if (player->takeDamage(1)) 
					{
						player->getGameObject()->getTransform()->setPosition(V3_START_POSITION.x, 300.0f, V3_START_POSITION.z + 10.0f);

						BasicCameraController *bsc = static_cast<BasicCameraController*>(player->getGameObject()->getCamera());
						bsc->setLookingAtTarget(true);
					} //dead
					else {} //still alive

					//(*iter)->getCollider()->setColliderType("");	// Disable collision happening again
					(*iter)->getCollider()->toggleActive();			// Disable collision happening again

					//Handle Collision (Current Primitive method)
					//int iDir = basicCameraController->getDir();
					//if (iDir > 0) basicCameraController->moveCamera("backward");
					//else basicCameraController->moveCamera("forward"); 
				}
				else // COMPLETED LEVEL 
				{
					player->getGameObject()->getTransform()->setPosition(V3_START_POSITION.x, 300.0f, V3_START_POSITION.z + 10.0f);

					BasicCameraController *bsc = static_cast<BasicCameraController*>(player->getGameObject()->getCamera());
					bsc->setLookingAtTarget(true);
				}
			}
		}
	}

	//==============================================================================
	// Check gameobjects colliding with one and other - COLLISION DETECTION
	//==============================================================================

	//Check gameobjects colliding with one and other
	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
	{
		//Store collider type
		/*std::string strColliderType = (*iter)->getCollider()->getColliderType();
		bool bResult;

		//if the collider type is box collider
		if (strColliderType == "BoxCollider") 
		{
			//Store original collider
			BoxCollider *boxCollider = static_cast<BoxCollider*>((*iter)->getCollider());

			//For all gameobjects compare to original collider
			for (auto iterCol = gameObjects.begin(); iter != gameObjects.end(); iterCol++)
			{
				//Collider to check against
				BoxCollider *otherBoxCollider = static_cast<BoxCollider*>((*iterCol)->getCollider());
				std::string strTestingType = (*iterCol)->getCollider()->getColliderType();

				if (strTestingType == "BoxCollider")
				{
					otherBoxCollider->withinColliderCheck(boxCollider);

					//if(collision detected) 
						//getVelocity and handle collision
							// handle the original object and the one it collides with
				}
			}
		}*/

		(*iter)->update(); // ================ !!!- GAMEOBJECT call to UPDATE - !!! ===================
	}

	return bPlayHitSound;
}

void SceneManager::cleanUp()
{
	if (skyBox)
	{
		skyBox->destroy();
		delete skyBox;
		skyBox = NULL;
	}
	auto iter = gameObjects.begin();
	while (iter != gameObjects.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete (*iter);
			(*iter) = NULL;
			iter = gameObjects.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	gameObjects.clear();
	floorTiles.clear();
	enemies.clear();
}

void SceneManager::initScene()
{
	//==============================================================================
	// !REQUIRED! GameObjects and Components
	//==============================================================================

	//Initialising MAIN CAMERA CONTROLLER
	basicCameraController = new BasicCameraController();								// Instantiate Basic Camera Controller (Camera Component)
	basicCameraController->setAspectRatio((float)(iWINDOW_WIDTH / iWINDOW_HEIGHT));		// Define aspect ratio
	basicCameraController->setFOV(45.0f);												// Set Field of View
	basicCameraController->setNearClip(0.1f);											// Set how close objects can be before clipped and not rendered
	basicCameraController->setFarClip(1000.0f);											// Set how far objects can be before clipped and not rendered

	//Initialise GAMEOBJECT that will HOLD BASIC CAMERA CONTROLLER (CAMERA COMPONENT)
	goMainCamera = new GameObject();													// Instantiate Camera GameObject
	basicCameraController->setParent(goMainCamera);										// Link BasicCameraController's Parent as GameObject
	goMainCamera->setName("MainCamera");												// Set name property in gameobject for main camera
	Transform *t = new Transform();														// Define new Transform for camera
	t->setPosition(V3_START_POSITION.x, V3_START_POSITION.y, V3_START_POSITION.z);													// Set Transform position
	goMainCamera->setTransform(t);														// Set Transform components onto the GameObject
	goMainCamera->setCamera(basicCameraController);										// Set GameObjects camera components to the basic camera controller

	//Initialise MAIN LIGHT
	Light * light = new Light();														// Instantiate main light (Light Component)
	light->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);									// Set Diffuse Colour

	//Initialise GAMEOBJECT that will HOLD MAIN LIGHT (LIGHT COMPONENT)
	goMainLight = new GameObject();														// Instantiate Light GameObject
	goMainLight->setName("MainLight");													// Set name property in gameobject for main light
	t = new Transform();																// Define new Transform for light
	t->setPosition(0.0f, 0.0f, 0.0f);													// Set Transform position
	goMainLight->setTransform(t);														// Set Transform component onto the GameObject
	goMainLight->setLight(light);														// Set GameObjects light component to the main light
	//goMainCamera->setLight(light);													// Set Main Camera's GameObject to as main light's light component

	//Add GameObjects to the vector for render, updating etc.
	gameObjects.push_back(goMainCamera);
	gameObjects.push_back(goMainLight);

	//createSkyBox();

	//==============================================================================
	// Define and link PLAYER components
	//==============================================================================

	player = new Player();
	player->setGameObject(goMainCamera);

	//==============================================================================
	// RANDOMLY GENERATE FLOOR PATH
	//==============================================================================

	iLevelSize = 100;
	iBuildDirection = 0;
	v3BuildPosition = V3_START_POSITION - vec3(0.0f, V3_START_POSITION.y + 2.5f, 0.0f);

	int i = iLevelSize;				// Counter for placing path segments
	int iTurnCount = rand() % 10;	// Counter for changing the build direction

	//Generate path with a level size of segments
	while (i > 0) 
	{
		instantiateFloorSegment(v3BuildPosition);
		incrementBuildPosition();
		i--;
		iTurnCount--;
		if (iTurnCount == 0) 
		{
			rotateBuildDirection();
			iTurnCount = rand() % 10;
			std::cout << "Random Turn Count " << iTurnCount << std::endl;
		}
	}

	//==============================================================================
	// RANDOMLY GENERATE PLANETS TO ROTATE ROUND 'BLACK HOLE'
	//==============================================================================

	v3BuildPosition += vec3(0.0f, 3.0f, 0.0f);
	//Generate asteroid storm
	i = 5;		// Counter for placing planets
	while (i > 0)
	{
		instantiatePlanet(v3BuildPosition, rand() % 60 + 10, rand() % 100 + 1);
		i--;
	}

	v3BuildPosition += vec3(0.0f, 2.0f, 0.0f);
	//Generate asteroid storm
	i = 2;		// Counter for Vehicles
	while (i > 0)
	{
		instantiateVehicle(v3BuildPosition, rand() % 30 + 10, rand() % 100 + 10);
		i--;
	}

	instantiateBlackHole(v3BuildPosition);	// !!! ========== - Path End Point - =========== !!!

	//==============================================================================
	// RANDOMLY GENERATE ENEMY BARRELS AROUND THE LEVEL
	//==============================================================================

	i = 10;		// Number of enemy barrel's
	while (i > 0)
	{
		v3BuildPosition = vec3(rand() % 100 + -50, 0.0f, rand() % 100 + -50);
		instantiateEnemyBarrel(v3BuildPosition);
		i--;
	}

	//==============================================================================
	// SHINY SHINY IN THE SKY
	//==============================================================================

	instantiateSun(vec3(0.0f,0.0f,0.0f));

	GameObject *goSprite = new GameObject();
	goSprite->setName("Health");
	t = new Transform();
	t->setPosition(-200.0f, -100.0f, -500.0f);
	CustomShape customShape = CustomShape();
	customShape.sprite(goSprite);
	goSprite->setTransform(t);

	Material *material = new Material();
	material->init();
	vsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLighttextureVS.glsl";
	fsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLighttextureFS.glsl";
	material->setSpecularPower(10.0f);
	material->setSpecularColour(0.0f, 0.0f, 0.0f, 0.0f);
	material->setDiffuseColour(0.0f, 0.0f, 0.0f, 0.0f);
	std::string strDiffuseMap = ASSET_PATH + TEXTURE_PATH + "starField.png";
	material->loadDiffuseMap(strDiffuseMap);
	material->loadShader(vsPath, fsPath);
	goSprite->setMaterial(material);



	goHealth = goSprite;

	gameObjects.push_back(goSprite);

	basicCameraController->addGameObjectToTargets(goSprite);

	//==============================================================================
	// Display the user with game commands
	//==============================================================================

	std::cout << "CONTROLS: Press F1 for 'help' (command list)" << std::endl;
	std::cout << "NAVIGATION:" << std::endl;
	std::cout << "[W]: Move camera FORWARD" << std::endl;
	std::cout << "[S]: Move camera BACKWARD" << std::endl;
	std::cout << "[A]: Rotate camera LEFT" << std::endl;
	std::cout << "[D]: Rotate camera RIGHT" << std::endl;
	std::cout << "[SPACE]: Move camera UP" << std::endl;
	std::cout << "[LEFT_SHIFT]: Move camera DOWN" << std::endl;
	std::cout << "OBJECT MANIPULATION" << std::endl;
	std::cout << "[CAPS_LOCK]: Target scene objects " << std::endl;
	std::cout << "[TAB]: Iterate through scene objects" << std::endl;
	std::cout << "...while locked onto an object" << std::endl;
	std::cout << "[Q]: Rotate positively round an object " << std::endl;
	std::cout << "[E]: Rotate negatively round an object" << std::endl;
	std::cout << "Change Rotate Axis" << std::endl;
	std::cout << "[1]: round the x-axis " << std::endl;
	std::cout << "[2]: round the y-axis " << std::endl;
	std::cout << "[3]: round the z-axis" << std::endl;
	std::cout << "...To move objects" << std::endl;
	std::cout << "[UP_ARROW][DOWN_ARROW][LEFT_ARROW][RIGHT_ARROW]" << std::endl;
	std::cout << "[B]: LINE MODE " << std::endl;
	std::cout << "[N]: POINT MODE" << std::endl;
	std::cout << "[M]: FILL MODE" << std::endl;

	//==============================================================================
	//Start Game Clock
	Timer::getTimer().start();
	//==============================================================================

}

void SceneManager::createSkyBox()
{
	Vertex triangleData[] = {
		{ vec3(-10.0f, 10.0f, 10.0f) },// Top Left
		{ vec3(-10.0f, -10.0f, 10.0f) },// Bottom Left
		{ vec3(10.0f, -10.0f, 10.0f) }, //Bottom Right
		{ vec3(10.0f, 10.0f, 10.0f) },// Top Right


									  //back
		{ vec3(-10.0f, 10.0f, -10.0f) },// Top Left
		{ vec3(-10.0f, -10.0f, -10.0f) },// Bottom Left
		{ vec3(10.0, -10.0f, -10.0f) }, //Bottom Right
		{ vec3(10.0f, 10.0f, -10.0f) }// Top Right
	};


	GLuint indices[] = {
		//front
		0, 1, 2,
		0, 3, 2,

		//left
		4, 5, 1,
		4, 1, 0,

		//right
		3, 7, 2,
		7, 6, 2,

		//bottom
		1, 5, 2,
		6, 2, 1,

		//top
		5, 0, 7,
		5, 7, 3,

		//back
		4, 5, 6,
		4, 7, 6
	};

	//creat mesh and copy in

	Mesh * pMesh = new Mesh();
	pMesh->init();

	pMesh->copyVertexData(8, sizeof(Vertex), (void**)triangleData);
	pMesh->copyIndexData(36, sizeof(int), (void**)indices);

	Transform *t = new Transform();
	t->setPosition(0.0f, 0.0f, 0.0f);
	//load textures and skybox material + Shaders
	SkyBoxMaterial *material = new SkyBoxMaterial();
	material->init();

	std::string vsPath = ASSET_PATH + SHADER_PATH + "/skyVS.glsl";
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/skyFS.glsl";
	material->loadShader(vsPath, fsPath);

	std::string posZTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysFront2048.png";
	std::string negZTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysBack2048.png";
	std::string posXTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysLeft2048.png";
	std::string negXTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysRight2048.png";
	std::string posYTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysUp2048.png";
	std::string negYTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysDown2048.png";

	material->loadCubeTexture(posZTexturename, negZTexturename, posXTexturename, negXTexturename, posYTexturename, negYTexturename);
	//create gameobject but don't add to queue!
	skyBox = new GameObject();
	skyBox->setMaterial(material);
	skyBox->setTransform(t);
	skyBox->setMesh(pMesh);
}

void SceneManager::incrementBuildPosition()
{
	//Based on the int representing NORTH, SOUTH etc build direction
	switch (iBuildDirection)
	{
		case 0: //Increment based on size of floor model
			v3BuildPosition = v3BuildPosition + vec3(0.0f, 0.0f, -2.0f);
			break;
		case 1:
			v3BuildPosition = v3BuildPosition + vec3(-2.0f, 0.0f, 0.0f);
			break;
		case 2:
			v3BuildPosition = v3BuildPosition + vec3(0.0f, 0.0f, 2.0f);
			break;
		case 3:
			v3BuildPosition = v3BuildPosition + vec3(2.0f, 0.0f, 0.0f);
			break;
	}
}

void SceneManager::rotateBuildDirection()
{
	int iRand = rand() % 10; // get random number between 0-10
	if (iRand > 5) iBuildDirection++; // 50-50 chance
	else iBuildDirection--;	// set direction based on high low

	//Limit Direction to 0-3
	if (iBuildDirection > 3) iBuildDirection = 0;
	if (iBuildDirection < 0) iBuildDirection = 3;

	std::cout << "Build Direction now is " << iBuildDirection << std::endl;
}

void SceneManager::instantiateVehicle(vec3 v3InstantiatePosition, float fDistanceToOrbit, float fOrbitSpeed)
{
	modelPath = ASSET_PATH + MODEL_PATH + "armoredrecon.fbx";							// Set string for model address
	texturePath = ASSET_PATH + TEXTURE_PATH + "armoredrecon_diff.png";					// Set string for texture Map address
	heightMap = ASSET_PATH + TEXTURE_PATH + "armoredrecon_Height.png";					// Set string for height map address
	specularMap = ASSET_PATH + TEXTURE_PATH + "armoredrecon_spec.png";					// Set string for specular map address

	//Initialise GAMEOBJECT that will HOLD THE PLANET(ArmorDrecon)
	GameObject * goArmorDrecon = loadFBXFromFile(modelPath, vec3(1.0f, 1.0f, 1.0f));		// Load model PLANET
	goArmorDrecon->gameObject = goArmorDrecon;												// Link with self
	goArmorDrecon->setName("ArmorDrecon");													// Set name property in PLANET's GameObject
	Transform *t = new Transform();															// Define new Transform for PLANET's GameObject
	t->setPosition(v3InstantiatePosition.x,
		v3InstantiatePosition.y,
		v3InstantiatePosition.z);															// Set Transform position
	goArmorDrecon->setTransform(t);															// Set Transform component onto the GameObject
	vsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureVS.glsl";					// Set string for Vertex Shader
	fsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureFS.glsl";					// Set string for Fragment Shader

																							//For all child objects attach a new MATERIAL LOAD VERTEX and FRAGMENT SHADER
	for (int i = 0; i < goArmorDrecon->getChildCount(); i++)
	{
		// Set MATERIAL Properties
		Material * material = new Material();											// Instantiate new material
		material->init();																// Initiate material
		material->loadDiffuseMap(texturePath);											// Load Diffuse Texture
		material->loadHeightMap(heightMap);												// Load Height Map
		material->loadSpecularMap(specularMap);											// Load Specular Map
		material->setSpecularPower(50.0f);												// Set Specular power for material
		material->setSpecularColour(1.0f, 1.0f, 1.0f, 1.0f);							// Set Specular colour for material
		material->loadShader(vsPath, fsPath);											// Load Vertex and Fragment Shader onto the material

		goArmorDrecon->getChild(i)->setMaterial(material);								// Set child material
	}

	// Initialise BOX COLLIDER for ArmorDrecon						
	SphereCollider *sphereCollider = new SphereCollider(20.0f);							// Instantiate Box Collider
	sphereCollider->setOffSet(vec3(0.0f, 0.0f, 0.0f));									// if collider needs be offset, delt with here
	sphereCollider->setParent(goArmorDrecon);											// Set Box Collider parent as the ArmorDrecons's GameObject
	goArmorDrecon->setCollider(static_cast<Collider*>(sphereCollider));					// Set the Collider component on the armordrecons as a cast box collider
	basicCameraController->addGameObjectToTargets(goArmorDrecon);						// Add the GameObjects the cameras list of objects to look at

	//Add GameObjects to the vector for render, updating etc.
	gameObjects.push_back(goArmorDrecon);

	//Create Planet properties and add it to be updated
	Planet *planetVehicle = new Planet(fDistanceToOrbit);
	planetVehicle->setGameObject(goArmorDrecon);
	planetVehicle->setOrbitSpeed(fOrbitSpeed / 10000);
	planetVehicle->setOrbitCenter(v3InstantiatePosition);
	planetVehicle->setRotateState(true);
	planets.push_back(planetVehicle);

	std::cout << "Placed Planet (Vehicle) at (" << v3BuildPosition.x << "," << v3BuildPosition.y << "," << v3BuildPosition.z << ")" << " Orbit Distance = " << fDistanceToOrbit << std::endl;
}

void SceneManager::instantiateEnemyBarrel(vec3 v3InstantiatePosition)
{
	modelPath = ASSET_PATH + MODEL_PATH + "barrel_1.fbx";
	texturePath = ASSET_PATH + TEXTURE_PATH + "barrel_1_diffuse.png";
	heightMap = ASSET_PATH + TEXTURE_PATH + "barrel_1_height.png";
	specularMap = ASSET_PATH + TEXTURE_PATH + "barrel_1_specular.png";

	GameObject * goOilBarrel = loadFBXFromFile(modelPath, vec3(1.0f, 1.0f, 1.0f));
	goOilBarrel->gameObject = goOilBarrel;
	goOilBarrel->setName("Oil Barrel");
	Transform *t = new Transform();
	t->setPosition(v3InstantiatePosition.x,
		v3InstantiatePosition.y,
		v3InstantiatePosition.z);
	goOilBarrel->setTransform(t);
	vsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureVS.glsl";
	fsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureFS.glsl";

	//For all child objects attach a new MATERIAL LOAD VERTEX and FRAGMENT SHADER
	for (int i = 0; i < goOilBarrel->getChildCount(); i++)
	{
		// Set MATERIAL Properties
		Material * material = new Material();
		material->init();
		material->loadDiffuseMap(texturePath);
		material->loadHeightMap(heightMap);
		material->loadSpecularMap(specularMap);
		material->setSpecularPower(50.0f);
		material->setSpecularColour(1.0f, 1.0f, 1.0f, 1.0f);
		material->loadShader(vsPath, fsPath);

		goOilBarrel->getChild(i)->setMaterial(material);
	}

	BoxCollider *boxCollider;
	boxCollider = new BoxCollider(2.0f, 2.0f, 2.0f);
	boxCollider->setParent(goOilBarrel);
	boxCollider->createColliderVertices();
	goOilBarrel->setCollider(static_cast<Collider*>(boxCollider));
	basicCameraController->addGameObjectToTargets(goOilBarrel);


	gameObjects.push_back(goOilBarrel);

	// Enemy
	Enemy *enemyBarrel = new Enemy();
	enemyBarrel->setDistanceToEngage(100.0f);
	enemyBarrel->setGameObject(goOilBarrel);
	enemyBarrel->setTarget(goMainCamera);

	enemies.push_back(enemyBarrel);

	//Create Planet properties and add it to be updated
	Planet *planetBarrel = new Planet(NULL);
	planetBarrel->setGameObject(goOilBarrel);
	planetBarrel->setOrbitState(false);
	planetBarrel->setRotateState(true);
	planets.push_back(planetBarrel);
}

void SceneManager::instantiateCustomShape(vec3 v3InstantiatePosition)
{
	GameObject *goShape = new GameObject();	
	goShape->gameObject = goShape;
	goShape->setName("Cube");
	Transform *t = new Transform();														
	t->setPosition(v3InstantiatePosition.x,
		v3InstantiatePosition.y,
		v3InstantiatePosition.z);
	goShape->setTransform(t);

	//Create custom shape geometry (cube)
	CustomShape customShape = CustomShape();
	customShape.init(goShape);

	Material *material = new Material();
	material->init();
	material->loadDiffuseMap("../assets/textures/grey.png");
	material->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	vsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureVS.glsl";
	fsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureFS.glsl";
	material->loadShader(vsPath, fsPath);
	goShape->setMaterial(material);

	// Instantiate BOX COLLIDER for Custom Shape - Box
	SphereCollider *sphereCollider = new SphereCollider(2.5f);
	sphereCollider->setOffSet(vec3(0.0f, 0.0f, 0.0f));
	sphereCollider->setParent(goShape);
	goShape->setCollider(static_cast<Collider*>(sphereCollider));
	basicCameraController->addGameObjectToTargets(goShape);

	gameObjects.push_back(goShape);
}

void SceneManager::instantiateFloorSegment(vec3 v3InstantiatePosition)
{
	modelPath = ASSET_PATH + MODEL_PATH + "cube.fbx";
	texturePath = ASSET_PATH + TEXTURE_PATH + "grey.png";

	GameObject * goFloorSegement = loadFBXFromFile(modelPath, vec3(30.0f, 30.0f, 30.0f));
	goFloorSegement->gameObject = goFloorSegement;
	goFloorSegement->setName("Ship Hull");
	Transform *t = new Transform();
	t->setRotation(270.0f, 0.0f, 0.0f);
	t->setPosition(v3InstantiatePosition.x, v3InstantiatePosition.y, v3InstantiatePosition.z);
	goFloorSegement->setTransform(t);
	vsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureVS.glsl";
	fsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureFS.glsl";

	//For all child objects attach a new MATERIAL LOAD VERTEX and FRAGMENT SHADER
	for (int i = 0; i < goFloorSegement->getChildCount(); i++)
	{
		// Set MATERIAL Properties
		Material * material = new Material();
		material->init();
		material->loadDiffuseMap("../assets/textures/grey.png");
		material->setSpecularPower(10.0f);
		material->setSpecularColour(1.0f, 1.0f, 0.0f, 1.0f);
		material->setDiffuseColour(0.3f, 0.3f, 0.3f, 1.0f);
		material->loadShader(vsPath, fsPath);

		goFloorSegement->getChild(i)->setMaterial(material);
	}

	// Initialise BOX COLLIDER for ArmorDrecon						
	BoxCollider *boxCollider = new BoxCollider(2.0f, 2.0f, 2.0f);
	boxCollider->setOffSet(vec3(0.0f,0.5f,0.0f));
	boxCollider->setParent(goFloorSegement);
	boxCollider->createColliderVertices();
	goFloorSegement->setCollider(static_cast<Collider*>(boxCollider));
	basicCameraController->addGameObjectToTargets(goFloorSegement);

	//Add GameObjects to the vector for render, updating etc.
	gameObjects.push_back(goFloorSegement);
	floorTiles.push_back(goFloorSegement);

	std::cout << "Placed Floor Tile (" << v3BuildPosition.x << "," << v3BuildPosition.y << "," << v3BuildPosition.z << ")" << std::endl;
}

void SceneManager::instantiateBlackHole(vec3 v3InstantiatePosition)
{
	modelPath = ASSET_PATH + MODEL_PATH + "sun.fbx";
	texturePath = ASSET_PATH + TEXTURE_PATH + "black.png";

	GameObject * goBlacHole = loadFBXFromFile(modelPath, vec3(10.0f, 10.0f, 10.0f));
	goBlacHole->gameObject = goBlacHole;
	goBlacHole->setName("BlackHole");  // DO NOT RENAME (Check in collision checks for name)
	Transform *t = new Transform();	
	t->setRotation(0.0f, 0.0f, 0.0f);
	t->setPosition(v3InstantiatePosition.x,
		v3InstantiatePosition.y,
		v3InstantiatePosition.z);
	goBlacHole->setTransform(t);
	vsPath = ASSET_PATH + SHADER_PATH + "/textureVS.glsl";
	fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";

	for (int i = 0; i < goBlacHole->getChildCount(); i++)
	{
		// Set MATERIAL Properties
		Material * material = new Material();
		material->init();
		material->loadDiffuseMap(texturePath);
		material->setSpecularPower(10.0f);
		material->setSpecularColour(1.0f, 1.0f, 0.0f, 1.0f);
		material->setDiffuseColour(0.3f, 0.3f, 0.3f, 1.0f);
		material->loadShader(vsPath, fsPath);

		goBlacHole->getChild(i)->setMaterial(material);
	}
			
	SphereCollider *sphereCollider = new SphereCollider(50.0f);
	sphereCollider->setOffSet(vec3(0.0f, 0.0f, 0.0f));
	sphereCollider->setParent(goBlacHole);
	goBlacHole->setCollider(static_cast<Collider*>(sphereCollider));
	basicCameraController->addGameObjectToTargets(goBlacHole);

	gameObjects.push_back(goBlacHole);

	std::cout << "Placed BlackHole at (" << v3BuildPosition.x << "," << v3BuildPosition.y << "," << v3BuildPosition.z << ")" <<  std::endl;
}

void SceneManager::instantiatePlanet(vec3 v3InstantiatePosition, float fDistanceToOrbit, float fOrbitSpeed)
{
	modelPath = ASSET_PATH + MODEL_PATH + "sun.fbx";
	texturePath = ASSET_PATH + TEXTURE_PATH + "grey.png";

	GameObject * goPlanet = loadFBXFromFile(modelPath, vec3(100.0f, 100.0f, 100.0f));
	goPlanet->gameObject = goPlanet;
	goPlanet->setName("Planet");
	Transform *t = new Transform();
	t->setRotation(270.0f, 0.0f, 0.0f);
	t->setPosition(v3InstantiatePosition.x,
		v3InstantiatePosition.y,
		v3InstantiatePosition.z);
	goPlanet->setTransform(t);
	vsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureVS.glsl";
	fsPath = ASSET_PATH + SHADER_PATH + "/DirectionalLightTextureFS.glsl";

	for (int i = 0; i < goPlanet->getChildCount(); i++)
	{
		// Set MATERIAL Properties
		Material * material = new Material();
		material->init();
		material->loadDiffuseMap(texturePath);
		material->setSpecularPower(10.0f);
		material->setSpecularColour(1.0f, 1.0f, 0.0f, 1.0f);
		material->setDiffuseColour(0.3f, 0.3f, 0.3f, 1.0f);
		material->loadShader(vsPath, fsPath);

		goPlanet->getChild(i)->setMaterial(material);
	}
					
	SphereCollider *sphereCollider = new SphereCollider(2.5f);
	sphereCollider->setOffSet(vec3(0.0f, 0.0f, 0.0f));
	sphereCollider->setParent(goPlanet);
	goPlanet->setCollider(static_cast<Collider*>(sphereCollider));
	basicCameraController->addGameObjectToTargets(goPlanet);

	Planet *planet = new Planet(fDistanceToOrbit);
	planet->setGameObject(goPlanet);
	planet->setOrbitSpeed(fOrbitSpeed / 10000);
	planet->setOrbitCenter(v3InstantiatePosition);
	planets.push_back(planet);

	gameObjects.push_back(goPlanet);

	std::cout << "Placed Planet at (" << v3BuildPosition.x << "," << v3BuildPosition.y << "," << v3BuildPosition.z << ")" << " Orbit Distance = " << fDistanceToOrbit << std::endl;
}

void SceneManager::instantiateSun(vec3 v3InstantiatePosition)
{
	modelPath = ASSET_PATH + MODEL_PATH + "sun.fbx";
	texturePath = ASSET_PATH + TEXTURE_PATH + "sunTexture.png";

	GameObject * goSun = loadFBXFromFile(modelPath, vec3(1.0f, 1.0f, 1.0f));
	goSun->gameObject = goSun;
	goSun->setName("The Sun");
	Transform *t = new Transform();
	float fOrbitDistance = 300.0f;
	t->setRotation(90.0f, 0.0f, 0.0f);
	t->setPosition(-5.0f, 0.0f, fOrbitDistance);
	goSun->setTransform(t);

	vsPath = ASSET_PATH + SHADER_PATH + "/textureVS.glsl";				// Set string for Vertex Shader
	fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";				// Set string for Fragment Shader

	Planet *planetSun = new Planet(fOrbitDistance);
	planetSun->setGameObject(goSun);
	planets.push_back(planetSun);

	//For all child objects attach a new MATERIAL LOAD VERTEX and FRAGMENT SHADER
	for (int i = 0; i < goSun->getChildCount(); i++)
	{
		// Set MATERIAL Properties
		Material * material = new Material();
		material->init();
		material->loadDiffuseMap(texturePath);
		material->setSpecularPower(10.0f);
		material->setSpecularColour(1.0f, 1.0f, 1.0f, 1.0f);
		material->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
		material->loadShader(vsPath, fsPath);					// Load Vertex and Fragment Shader onto the material

		goSun->getChild(i)->setMaterial(material);
	}

	basicCameraController->addGameObjectToTargets(goSun);
	gameObjects.push_back(goSun);
}