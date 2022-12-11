#include "PhysicsCapsule.h"

PhysicsCapsule::PhysicsCapsule(string name, void* shaderByteCode, size_t sizeShader, float length, float radius, PrimitiveType type) : Capsule(name, shaderByteCode, sizeShader, 2, 1, PrimitiveType::PCAPSULE)
{
	this->type = PrimitiveType::PCAPSULE;
	this->ComputeLocalMatrix();
	this->attachComponent(new PhysicsComponent(("PhysicsComponent"), this));
}

PhysicsCapsule::~PhysicsCapsule()
{
	Capsule::~Capsule();
}

void PhysicsCapsule::update(float deltaTime)
{
	Capsule::update(deltaTime);
}

void PhysicsCapsule::draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right)
{
	Capsule::draw(w, h, vs, ps, forward, right);
}
