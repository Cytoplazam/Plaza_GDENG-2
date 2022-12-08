#include "Sphere.h"

Sphere::Sphere(string name, void* shaderByteCode, size_t sizeShader, PrimitiveType type) :GameObject(name, PrimitiveType::SPHERE)
{

}

Sphere::~Sphere()
{
	this->vbt->release();
	this->ib->release();
	GameObject::~GameObject();
}

void Sphere::update(float deltaTime)
{
}

void Sphere::draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right)
{

}

void Sphere::setAnimSpeed(float speed)
{
}
