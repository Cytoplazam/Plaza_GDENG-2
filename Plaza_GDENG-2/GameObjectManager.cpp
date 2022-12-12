#include "GameObjectManager.h"
#include <iostream>

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::get()
{
	return sharedInstance;
}

void GameObjectManager::init()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	delete sharedInstance;
}

GameObject* GameObjectManager::findObjectByName(string name)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->getName() == name)
			return objects[i];
	}
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
	return objects;
}

void GameObjectManager::updateAll()
{
	for (int i = 0; i < objects.size(); i++)
	{
		this->objects[i]->update(EngineTime::getDeltaTime());
	}
}

void GameObjectManager::renderAll(int h, int w, float fwd, float rgt)
{
	/*if (pCubes.size() > 0)
	{
		for (int i = 0; i < pCubes.size(); i++)
		{
			this->pCubes[i]->draw(w, h, this->m_vst, this->m_pst, fwd, rgt);
		}
	}
	if (pPlanes.size() > 0)
	{
		for (int i = 0; i < pPlanes.size(); i++)
		{
			this->pPlanes[i]->draw(w, h, this->m_vst, this->m_pst, fwd, rgt);
		}
	}*/
	for (int i = 0; i < objects.size(); i++)
	{
		this->objects[i]->draw(w, h, this->m_vst, this->m_pst, fwd, rgt);
	}
}

void GameObjectManager::addObject(GameObject* gameObj)
{
	this->objects.push_back(gameObj);
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)// , Vector3D rot, Vector3D pos, Vector3D scale)
{
	GraphicsEngine::get()->compileVertexShader(L"VertexShaderTex.hlsl", "vsmain", &shaderByteCode, &sizeShader);

	m_vst = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

	if (type == PrimitiveType::PCUBE)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->pCubes.size() > 0)
				name = "PhysicsCube(" + to_string(this->pCubes.size()) + ")";
			else
				name = "PhysicsCube";

			PhysicsCube* pcubeObject = new PhysicsCube(name, shaderByteCode, sizeShader);

			this->addObject(pcubeObject);
			this->pCubes.push_back(pcubeObject);
		}
	}
	if (type == PrimitiveType::CUBE)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->Cubes.size() > 0)
				name = "Cube(" + to_string(this->Cubes.size()) + ")";
			else
				name = "Cube";
			
			Cube* cubeObject = new Cube(name, shaderByteCode, sizeShader, GameObject::CUBE);
				
			this->addObject(cubeObject);
			this->Cubes.push_back(cubeObject);
		}
	}
	if (type == PrimitiveType::PLANE)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->Planes.size() > 0)
				name = "Plane(" + to_string(this->Planes.size()) + ")";
			else
				name = "Plane";

			Plane* plane = new Plane(name, shaderByteCode, sizeShader, GameObject::PLANE);

			this->addObject(plane);
			this->Planes.push_back(plane);
		}
			
	}
	if (type == PrimitiveType::PPLANE)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->pPlanes.size() > 0)
				name = "PhysicsPlane(" + to_string(this->pPlanes.size()) + ")";
			else
				name = "PhysicsPlane";

			PhysicsPlane* pPlane = new PhysicsPlane(name, shaderByteCode, sizeShader);

			this->addObject(pPlane);
			this->pPlanes.push_back(pPlane);
		}
	}
	if (type == PrimitiveType::SPHERE)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->spheres.size() > 0)
				name = "Sphere(" + to_string(this->spheres.size()) + ")";
			else
				name = "Sphere";

			Sphere* sphere = new Sphere(name, shaderByteCode, sizeShader, 1, 24, 24, GameObject::SPHERE);

			this->addObject(sphere);
			this->spheres.push_back(sphere);
		}
	}
	if (type == PrimitiveType::PSPHERE)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->pSpheres.size() > 0)
				name = "PhysicsSphere(" + to_string(this->pSpheres.size()) + ")";
			else
				name = "PhysicsSphere";

			PhysicsSphere* pSphere = new PhysicsSphere(name, shaderByteCode, sizeShader, 1, 24, 24, GameObject::PSPHERE);

			this->addObject(pSphere);
			this->pSpheres.push_back(pSphere);
		}
	}
	if (type == PrimitiveType::CAPSULE)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->capsules.size() > 0)
				name = "Capsule(" + to_string(this->capsules.size()) + ")";
			else
				name = "Capsule";

			Capsule* capsule = new Capsule(name, shaderByteCode, sizeShader, 2, 1, GameObject::CAPSULE);

			this->addObject(capsule);
			this->capsules.push_back(capsule);
		}
	}
	if (type == PrimitiveType::PCAPSULE)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->pCapsules.size() > 0)
				name = "PhysicsCapsule(" + to_string(this->pCapsules.size()) + ")";
			else
				name = "PhysicsCapsule";

			PhysicsCapsule* pCapsule = new PhysicsCapsule(name, shaderByteCode, sizeShader, 2, 1, GameObject::PCAPSULE);

			this->addObject(pCapsule);
			this->pCapsules.push_back(pCapsule);
		}
	}
	if (type == PrimitiveType::TEAPOT)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->teapots.size() > 0)
				name = "Teapot(" + to_string(this->pCapsules.size()) + ")";
			else
				name = "Teapot";

			OBJ* teapot = new OBJ(name, shaderByteCode, sizeShader);

			this->addObject(teapot);
			this->teapots.push_back(teapot);
		}
	}
	if (type == PrimitiveType::BUNNY)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->bunnies.size() > 0)
				name = "Bunny(" + to_string(this->bunnies.size()) + ")";
			else
				name = "Bunny";

			OBJb* bunny = new OBJb(name, shaderByteCode, sizeShader);

			this->addObject(bunny);
			this->bunnies.push_back(bunny);
		}
	}
	if (type == PrimitiveType::ARMADILLO)
	{
		for (int i = 0; i < 1; i++)
		{
			string name;

			if (this->armadillos.size() > 0)
				name = "Armadillo(" + to_string(this->armadillos.size()) + ")";
			else
				name = "Armadillo";

			OBJa* armadillo = new OBJa(name, shaderByteCode, sizeShader);

			this->addObject(armadillo);
			this->armadillos.push_back(armadillo);
		}
	}
	

	GraphicsEngine::get()->compilePixelShader(L"PixelShaderTex.hlsl", "psmain", &shaderByteCode, &sizeShader);

	m_pst = GraphicsEngine::get()->createPixelShader(shaderByteCode, sizeShader);

	GraphicsEngine::get()->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	::memcpy(m_mesh_layout_byte_code, shaderByteCode, sizeShader);
	m_mesh_layout_size = sizeShader;
}

void GameObjectManager::createObjectFromFile(GameObject::PrimitiveType type, void* shaderByteCode, size_t sizeShader, string name, Vector3D rot, Vector3D pos, Vector3D scale)
{
	GraphicsEngine::get()->compileVertexShader(L"VertexShaderTex.hlsl", "vsmain", &shaderByteCode, &sizeShader);

	m_vst = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

	if (type == GameObject::PrimitiveType::PCUBE)
	{
		string tempName;

		if (this->pCubes.size() > 0)
			tempName = "PhysicsCube(" + to_string(this->pCubes.size()) + ")";
		else
			tempName = "PhysicsCube";

		PhysicsCube* pcubeObject = new PhysicsCube(tempName, shaderByteCode, sizeShader);
		pcubeObject->setScale(scale);
		pcubeObject->setPos(pos);
		pcubeObject->setRot(rot);
		this->addObject(pcubeObject);
		this->pCubes.push_back(pcubeObject);
	}
	if (type == GameObject::PrimitiveType::CUBE)
	{
		string tempName;

		if (this->Cubes.size() > 0)
			tempName = "Cube(" + to_string(this->Cubes.size()) + ")";
		else
			tempName = "Cube";

		Cube* cubeObject = new Cube(tempName, shaderByteCode, sizeShader, GameObject::CUBE);
		cubeObject->setScale(scale);
		cubeObject->setPos(pos);
		cubeObject->setRot(rot);
		this->addObject(cubeObject);
		this->Cubes.push_back(cubeObject);
	}
	if (type == GameObject::PrimitiveType::PLANE)
	{
		string tempName;

		if (this->Planes.size() > 0)
			tempName = "Plane(" + to_string(this->Planes.size()) + ")";
		else
			tempName = "Plane";

		Plane* plane = new Plane(tempName, shaderByteCode, sizeShader, GameObject::PLANE);
		plane->setScale(scale);
		plane->setPos(pos);
		plane->setRot(rot);
		this->addObject(plane);
		this->Planes.push_back(plane);
	}
	if (type == GameObject::PrimitiveType::PPLANE)
	{
		string tempName;

		if (this->pPlanes.size() > 0)
			tempName = "PhysicsPlane(" + to_string(this->pPlanes.size()) + ")";
		else
			tempName = "PhysicsPlane";

		PhysicsPlane* pPlane = new PhysicsPlane(tempName, shaderByteCode, sizeShader);
		pPlane->setScale(scale);
		pPlane->setPos(pos);
		pPlane->setRot(rot);
		this->addObject(pPlane);
		this->pPlanes.push_back(pPlane);
	}
	if (type == GameObject::PrimitiveType::SPHERE)
	{
		string tempName;

		if (this->spheres.size() > 0)
			tempName = "Sphere(" + to_string(this->spheres.size()) + ")";
		else
			tempName = "Sphere";

		Sphere* sphere = new Sphere(tempName, shaderByteCode, sizeShader, 1, 24, 24, GameObject::SPHERE);
		sphere->setScale(scale);
		sphere->setPos(pos);
		sphere->setRot(rot);
		this->addObject(sphere);
		this->spheres.push_back(sphere);
	}
	if (type == GameObject::PrimitiveType::PSPHERE)
	{
		string tempName;

		if (this->pSpheres.size() > 0)
			tempName = "PhysicsSphere(" + to_string(this->pSpheres.size()) + ")";
		else
			tempName = "PhysicsSphere";

		PhysicsSphere* pSphere = new PhysicsSphere(tempName, shaderByteCode, sizeShader, 1, 24, 24, GameObject::PSPHERE);
		pSphere->setScale(scale);
		pSphere->setPos(pos);
		pSphere->setRot(rot);
		this->addObject(pSphere);
		this->pSpheres.push_back(pSphere);
	}
	if (type == GameObject::PrimitiveType::CAPSULE)
	{
		string tempName;

		if (this->capsules.size() > 0)
			tempName = "Capsule(" + to_string(this->capsules.size()) + ")";
		else
			tempName = "Capsule";

		Capsule* capsule = new Capsule(tempName, shaderByteCode, sizeShader, 2, 1, GameObject::CAPSULE);
		capsule->setScale(scale);
		capsule->setPos(pos);
		capsule->setRot(rot);
		this->addObject(capsule);
		this->capsules.push_back(capsule);
	}
	if (type == GameObject::PrimitiveType::PCAPSULE)
	{
		string tempName;

		if (this->pCapsules.size() > 0)
			tempName = "PhysicsCapsule(" + to_string(this->pCapsules.size()) + ")";
		else
			tempName = "PhysicsCapsule";

		PhysicsCapsule* pCapsule = new PhysicsCapsule(tempName, shaderByteCode, sizeShader, 2, 1, GameObject::PCAPSULE);
		pCapsule->setScale(scale);
		pCapsule->setPos(pos);
		pCapsule->setRot(rot);
		this->addObject(pCapsule);
		this->pCapsules.push_back(pCapsule);
	}

	GraphicsEngine::get()->compilePixelShader(L"PixelShaderTex.hlsl", "psmain", &shaderByteCode, &sizeShader);

	m_pst = GraphicsEngine::get()->createPixelShader(shaderByteCode, sizeShader);

	GraphicsEngine::get()->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	::memcpy(m_mesh_layout_byte_code, shaderByteCode, sizeShader);
	m_mesh_layout_size = sizeShader;
	
	//std::cout << "Created a " << name << " with Rotation: " << to_string(rot.m_x) << ", " << to_string(rot.m_y) << ", " << to_string(rot.m_y);
}

void GameObjectManager::delObject(GameObject* gameObj)
{
	delete gameObj;
}

void GameObjectManager::delObjectByName(string name)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->getName() == name)
		{
			this->delObject(objects[i]);
			break;
		}
	}
}

void GameObjectManager::setSelectedObject(GameObject* gameObj)
{
	this->selectedObj = gameObj;
}

GameObject* GameObjectManager::getSelectedObject()
{
	return selectedObj;
}
