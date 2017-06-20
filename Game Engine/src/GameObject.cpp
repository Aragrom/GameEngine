#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"
#include "Collider.h"

// Constructor
GameObject::GameObject()
{
    m_Transform=NULL;
    m_Mesh=NULL;
    m_Material=NULL;
    m_Camera=NULL;
	m_Light = NULL;
	m_Collider = NULL;
    m_Name="GameObject";
	m_Parent = NULL;
}

// Deconstructor
GameObject::~GameObject()
{

}

// Call init() on all components and child components
void GameObject::init()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}

	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		(*iter)->init();
	}
}

// Call update() on all components and child components
void GameObject::update()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->update();
	}

	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		(*iter)->update();
	}
    
}

// Call render() on all components and child components
void GameObject::render()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->render();
	}

	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		(*iter)->render();
	}
    
}

// Call destroy() on all components and child components
void GameObject::destroy()
{
    auto iter=m_Components.begin();
	while(iter!=m_Components.end())
    {
        (*iter)->destroy();
        if ((*iter))
        {
            delete (*iter);
            (*iter)=NULL;
            iter=m_Components.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    m_Components.clear();

	auto gameObjiter = m_Children.begin();
	while (gameObjiter != m_Children.end())
	{
		(*gameObjiter)->destroy();
		if ((*gameObjiter))
		{
			delete (*gameObjiter);
			(*gameObjiter) = NULL;
			gameObjiter = m_Children.erase(gameObjiter);
		}
		else
		{
			gameObjiter++;
		}
	}
	m_Children.clear();
    
}

// Take component add it to component list and set parent of component to this GameObject
void GameObject::addComponent(Component * component)
{
    component->setParent(this);
    m_Components.push_back(component);
}

// Set name property of this GameObject
void GameObject::setName(const std::string& name)
{
    m_Name=name;
}

// Get name property (string)
const std::string& GameObject::getName()
{
    return m_Name;
}

// Take Pointer to Transform component and add it to this GameObject's Transform component
void GameObject::setTransform(Transform * transform)
{
    m_Transform=transform;
    addComponent(transform);
}

// Take Pointer to Mesh component and add it to this GameObject's Mesh component
void GameObject::setMesh(Mesh * mesh)
{
    m_Mesh=mesh;
    addComponent(mesh);
}

// Take Pointer to Material component and add it to this GameObject's Material component
void GameObject::setMaterial(BaseMaterial * material)
{
    m_Material=material;
    addComponent(material);
}

// Take Pointer to Camera component and add it to this GameObject's Camera component
void GameObject::setCamera(Camera * camera)
{
    m_Camera=camera;
    addComponent(camera);
}

// Take Pointer to Light component and add it to this GameObject's light component
void GameObject::setLight(Light * light)
{
	m_Light = light;
	addComponent(light);
}

// Take Pointer to Collider component and add it to this GameObject's Collider component
void GameObject::setCollider(Collider *collider)
{
	m_Collider = collider;
	collider->setParent(gameObject); // Set collider parent component to this GameObject (Link with self)
}

// Getter - Return Pointer to this GameObject's Transform
Transform * GameObject::getTransform()
{
    return m_Transform;
}

// Getter - Return Pointer to this GameObject's Mesh
Mesh * GameObject::getMesh()
{
    return m_Mesh;
}

// Getter - Return Pointer to this GameObject's Material
BaseMaterial * GameObject::getMaterial()
{
    return m_Material;
}

// Getter - Return Pointer to this GameObject's Camera
Camera * GameObject::getCamera()
{
    return m_Camera;
}

// Getter - Return Pointer to this GameObject's Light
Light * GameObject::getLight()
{
	return m_Light;
}

// Getter - Return Pointer to this GameObject's Collider
Collider * GameObject::getCollider()
{
	return m_Collider;
}

// Takes a GameObject Pointer and add it to the vector of child GameObjects
void GameObject::addChild(GameObject * obj)
{
	obj->setParent(this);
	m_Children.push_back(obj);
}

// Set this GameObjects Parent property sending a pointer to a GameObject
void GameObject::setParent(GameObject *parent)
{
	m_Parent = parent;
}

// Get this GameObjects Parent Property pointer
GameObject *GameObject::getParent()
{
	return m_Parent;
}

// Return integer representing the number of child GameObject's this GameObject has
int GameObject::getChildCount()
{
	return m_Children.size();
}

// Return a child GameObject pointer using its index
GameObject * GameObject::getChild(int index)
{
	if (index < m_Children.size())
		return m_Children[index];
	else
		return NULL;
}

// Get GameObject's component pointer based on a string representing a component type
Component * GameObject::getComponentByType(const std::string& type)
{
    Component *found=NULL;
    //std::find_if(m_Components.begin(),m_Components.end(),[type](Component &n){return n.getType()==type;});
    return found;
}

Component * GameObject::getComponentByName(const std::string& name)
{
    Component *found=NULL;
    //std::find_if(m_Components.begin(),m_Components.end(),[type](Component &n){return n.getType()==type;});
    return found;
}
