#pragma once
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "Cube.h"
#include "Plane.h"
#include "Sphere.h"
#include "Capsule.h"
#include "PhysicsSphere.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"
#include "PhysicsCapsule.h"
#include "OBJ.h";
#include "OBJa.h";
#include "OBJb.h";
#include "Vector3D.h"
#include "EngineTime.h"
#include "SceneWriter.h"
#include "HeirarchyScreen.h"
#include <unordered_map>

class GameObjectManager
{
	typedef std::string String;
	typedef std::vector<GameObject*> List;
	typedef std::unordered_map<String, GameObject*> HashTable;

public:
	enum PrimitiveType
	{
		CUBE, PCUBE,
		PLANE, PPLANE,
		SPHERE, PSPHERE,
		CAPSULE, PCAPSULE,
		TEAPOT, BUNNY, ARMADILLO
	};

	static GameObjectManager* get();
	static void init();
	static void destroy();

	GameObject* findObjectByName(string name);
	List getAllObjects();
	void updateAll();
	void renderAll(int h, int w, float fwd, float rgt);
	void addObject(GameObject* gameObj);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void createObjectFromFile(GameObject::PrimitiveType type, void* shaderByteCode, size_t sizeShader, string name, Vector3D rot, Vector3D pos, Vector3D scale);
	void delObject(GameObject* gameObj);
	void delObjectByName(string name);
	void setSelectedObject(GameObject* gameObj);
	GameObject* getSelectedObject();

private:
	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;

private:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* sharedInstance;

	std::vector<Cube*> Cubes;
	std::vector<PhysicsCube*> pCubes;
	std::vector<Plane*> Planes;
	std::vector<PhysicsPlane*> pPlanes;
	std::vector<GameObject*> objects;
	std::vector<Sphere*> spheres;
	std::vector<PhysicsSphere*> pSpheres;
	std::vector<Capsule*> capsules;
	std::vector<PhysicsCapsule*> pCapsules;
	std::vector<OBJ*> teapots;
	std::vector<OBJa*> armadillos;
	std::vector<OBJb*> bunnies;

	GameObject* selectedObj;

	VertexShader* m_vst;
	PixelShader* m_pst;
	friend class SceneWriter;
	friend class HeirarchyScreen;
};