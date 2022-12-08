#include "PhysicsCube.h"
#include "Math.h"

PhysicsCube::PhysicsCube(string name, void* shaderByteCode, size_t sizeShader): Cube(name, shaderByteCode, sizeShader, PrimitiveType::PCUBE)
{
	srand(time(NULL));
	float x = float(rand()) / float(RAND_MAX) * (5.0f - -1.0f) + -1.0f;
	float y = 4.0f;
	float z = float(rand()) / float(RAND_MAX) * (5.0f - -1.0f) + -1.0f;
	this->setPos(Vector3D(x, y, z));
	this->setScale(Vector3D(1.0f, 1.0f, 1.0f));
	this->type = PrimitiveType::PCUBE;
	this->ComputeLocalMatrix();
	this->attachComponent(new PhysicsComponent(("PhysicsComponent"), this));
}

PhysicsCube::~PhysicsCube()
{
}

void PhysicsCube::update(float deltaTime)
{
	Cube::update(deltaTime);
}

void PhysicsCube::draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right)
{
	Cube::draw(w, h, vs, ps, forward, right);
}
