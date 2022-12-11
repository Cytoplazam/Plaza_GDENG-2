#include "PhysicsSphere.h"

PhysicsSphere::PhysicsSphere(string name, void* shaderByteCode, size_t sizeShader, float radius, int stack, int sector, PrimitiveType type): Sphere(name, shaderByteCode, sizeShader, 1 ,24, 24, PrimitiveType::PSPHERE)
{
	this->type = PrimitiveType::PSPHERE;
	this->ComputeLocalMatrix();
	this->attachComponent(new PhysicsComponent(("PhysicsComponent"), this));
}

PhysicsSphere::~PhysicsSphere()
{
	Sphere::~Sphere();
}

void PhysicsSphere::update(float deltaTime)
{
	Sphere::update(deltaTime);
}

void PhysicsSphere::draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right)
{
	Sphere::draw(w, h, vs, ps, forward, right);
}
