#include "BaseComponentSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = NULL;

BaseComponentSystem* BaseComponentSystem::get()
{
	return sharedInstance;
}

void BaseComponentSystem::init()
{
	sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::destroy()
{
	delete sharedInstance;
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
	return this->physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
	this->physicsSystem = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
}
