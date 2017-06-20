#ifndef GameObject_h
#define GameObject_h

#include <string>
#include <vector>

class Component;
class Transform;
class Mesh;
class BaseMaterial;
class Camera;
class Light;
class Collider;
class Sphere;

class GameObject
{
public:
    
	// Setters
	void addComponent(Component * component);
    
	void setName(const std::string& name);
    void setTransform(Transform * transform);
    void setMesh(Mesh * mesh);
	void setMaterial(BaseMaterial * material);
    void setCamera(Camera * camera);
	void setLight(Light * light);
	void setCollider(Collider *collider);

	void addChild(GameObject * obj);
	void setParent(GameObject *parent);

	// Getters    
	GameObject *getParent();
	const std::string& getName();
	Transform * getTransform();
    Mesh *getMesh();
	BaseMaterial *getMaterial();
    Camera * getCamera();
	Light* getLight();
	Collider *getCollider();

	int getChildCount();
	GameObject * getChild(int index);

    Component * getComponentByType(const std::string& type);
    Component * getComponentByName(const std::string& name);

	GameObject();	// Constructor
	~GameObject();	// Deconstructor
	GameObject *gameObject; //For linking with self

	void init();
	void update();
	void render();
	void destroy();

private:

    std::vector<Component*> m_Components;	// Store Vector of Pointers to Components that the GameObjects has
	std::vector<GameObject*> m_Children;	// Store Vector of Pointers to GameObject representing the GameObjects children
	
	std::string m_Name;    
    Transform *m_Transform;					
    Mesh *m_Mesh;
	BaseMaterial *m_Material;
    Camera *m_Camera;
	Light *m_Light;
	Collider *m_Collider;
	GameObject *m_Parent;
};


#endif
