#include "GameObject.h"

GameObject::GameObject(string name)
{
	this->name = name;
	this->rot = Vector3D::zeros();
	this->pos = Vector3D::zeros();
	this->scale = Vector3D::ones();
}

GameObject::~GameObject()
{
}

void GameObject::setPos(float x, float y, float z)
{
	this->pos = Vector3D(x, y, z);
}

void GameObject::setPos(Vector3D pos)
{
	this->pos = pos;
}

Vector3D GameObject::getLocalPosition()
{
	return this->pos;
}

void GameObject::setScale(float x, float y, float z)
{
	this->scale = Vector3D(x, y, z);
}

void GameObject::setScale(Vector3D scale)
{
	this->scale = scale;
}

Vector3D GameObject::getLocalScale()
{
	return this->scale;
}

void GameObject::setRot(float x, float y, float z)
{
	this->rot = Vector3D(x, y, z);
}

void GameObject::setRot(Vector3D rot)
{
	this->rot = rot;
}

Vector3D GameObject::getLocalRotation()
{
	return this->rot;
}

string GameObject::getName()
{
	return this->name;
}
