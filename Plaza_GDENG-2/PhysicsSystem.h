#pragma once

#include "EngineTime.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>
#include "PhysicsComponent.h"

using namespace reactphysics3d;

class PhysicsComponent;

class PhysicsSystem
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
	typedef std::vector<PhysicsComponent*> ComponentList;

	PhysicsSystem();
	~PhysicsSystem();

	void registerComponent(PhysicsComponent* component);
	void unregisterComponent(PhysicsComponent* component);
	PhysicsComponent* findComponentByName(String name);
	ComponentList getAllComponents();

	void updateAllComponents();
	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

private:
	ComponentTable compTable;
	ComponentList compList;

private:
	PhysicsCommon* physCommon;
	PhysicsWorld* physWorld;

	float ticks = 0.0f;
};

