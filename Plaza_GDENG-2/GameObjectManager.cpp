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
		for (int i = 0; i < 3; i++)
		{
			//float x = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
			//float y = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
			//float z = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;

			PhysicsCube* pcubeObject = new PhysicsCube("PhysicsCube", shaderByteCode, sizeShader);
			//cubeObject->setAnimSpeed(float(rand()) / float(RAND_MAX) * (3.75f - -3.75f) + -3.75f);
			/*if (i == 0)
				cubeObject->setPos(Vector3D(0, 0.9f, 0));
			else if (i == 1)
				cubeObject->setPos(Vector3D(-1.5f, 2.0f, 0));
			else if (i == 2)
				cubeObject->setPos(Vector3D(-1.5f, 3.0f, -2.0f));*/
				//pcubeObject->setPos(Vector3D(0.0f, 0.0f, 3.0f));
				//pcubeObject->setRot(Vector3D(0.0f, 0.0f, 0.0f));
				//pcubeObject->setScale(Vector3D(1.0f, 1.0f, 1.0f));
			/*pcubeObject->setScale(scale);
			pcubeObject->setPos(pos);
			pcubeObject->setRot(rot);*/
			this->addObject(pcubeObject);
		}
	}
	if (type == PrimitiveType::CUBE)
	{
		for (int i = 0; i < 3; i++)
		{
			string name;

			if (i > 0)
				name = "Cube(" + to_string(i) + ")";
			else
				name = "Cube";
				
			
			Cube* cubeObject = new Cube(name, shaderByteCode, sizeShader, GameObject::CUBE);
			if (i == 0)
			{
				cubeObject->setPos(Vector3D(2, 2, 2));
				cubeObject->setRot(Vector3D(2, 2, 2));
			}
			else if (i == 1)
			{
				cubeObject->setPos(Vector3D(5, 5, 5));
				cubeObject->setRot(Vector3D(5, 5, 5));
			}
			else 
			{
				cubeObject->setPos(Vector3D(8, 8, 8));
				cubeObject->setRot(Vector3D(8, 8, 8));
			}
				
			this->addObject(cubeObject);
		}
	}
	if (type == PrimitiveType::PLANE)
	{
			Plane* plane = new Plane("Plane", shaderByteCode, sizeShader, GameObject::PLANE);
			this->addObject(plane);
	}
	if (type == PrimitiveType::PPLANE)
	{
		for (int i = 0; i < 1; i++)
		{
			PhysicsPlane* pPlane = new PhysicsPlane("PhysicsPlane", shaderByteCode, sizeShader);
			/*pPlane->setScale(scale);
			pPlane->setPos(pos);
			pPlane->setRot(rot);*/
			this->addObject(pPlane);
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
		PhysicsCube* pcubeObject = new PhysicsCube(name, shaderByteCode, sizeShader);
		pcubeObject->setScale(scale);
		pcubeObject->setPos(pos);
		pcubeObject->setRot(rot);
		this->addObject(pcubeObject);
	}
	if (type == GameObject::PrimitiveType::CUBE)
	{
		Cube* cubeObject = new Cube(name, shaderByteCode, sizeShader, GameObject::CUBE);
		cubeObject->setScale(scale);
		cubeObject->setPos(pos);
		cubeObject->setRot(rot);
		this->addObject(cubeObject);
	}
	if (type == GameObject::PrimitiveType::PLANE)
	{
		Plane* plane = new Plane(name, shaderByteCode, sizeShader, GameObject::PLANE);
		plane->setScale(scale);
		plane->setPos(pos);
		plane->setRot(rot);
		this->addObject(plane);
	}
	if (type == GameObject::PrimitiveType::PPLANE)
	{
		PhysicsPlane* pPlane = new PhysicsPlane(name, shaderByteCode, sizeShader);
		pPlane->setScale(scale);
		pPlane->setPos(pos);
		pPlane->setRot(rot);
		this->addObject(pPlane);
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

void GameObjectManager::setSelectedObject(string name)
{
}

void GameObjectManager::setSelectedObject(GameObject* gameObj)
{
}

GameObject* GameObjectManager::getSelectedObject()
{
	return selectedObj;
}
