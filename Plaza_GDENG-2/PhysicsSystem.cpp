#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
	this->physCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings world;
	world.defaultVelocitySolverNbIterations = 50;
	world.gravity = Vector3(0, -9.81, 0);
	this->physWorld = this->physCommon->createPhysicsWorld(world);
}

PhysicsSystem::~PhysicsSystem()
{
	this->compList.clear();
	this->compTable.clear();
	this->physCommon = nullptr;
	this->physWorld = nullptr;
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	this->compList.push_back(component);
	this->compTable[component->getName()] = component;
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	this->compTable.erase(component->getName());
	int i = -1;
	for (int j = 0; j < this->compList.size(); i++)
	{
		if (this->compList[i]->getName() == component->getName())
		{
			j = i;
			this->compList.erase(this->compList.begin() + i);
			break;
		}
	}
}

PhysicsComponent* PhysicsSystem::findComponentByName(String name)
{
	return this->compTable.at(name);
}

PhysicsSystem::ComponentList PhysicsSystem::getAllComponents()
{
	return this->compList;
}

void PhysicsSystem::updateAllComponents()
{
	if (EngineTime::getDeltaTime() > 0.0f)
	{
		this->physWorld->update(EngineTime::getDeltaTime());
		for (int i = 0; i < this->compList.size(); i++)
		{
			this->compList[i]->perform(EngineTime::getDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physCommon;
}
