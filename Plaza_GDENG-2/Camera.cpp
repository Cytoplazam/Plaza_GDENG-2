#include "Camera.h"
#include <iostream>

Camera::Camera(string name) :GameObject(name, PrimitiveType::CAMERA)
{
	this->setPos(0, 0, -2);
	InputSystem::get()->addListener(this);
	this->updateViewMatrix();
}

Camera::~Camera()
{
}

void Camera::draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right)
{
}

void Camera::update(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float movespeed = 10.f;

	if (InputSystem::get()->isKeyDown('W'))
	{
		z += deltaTime * movespeed;
		this->setPos(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('S'))
	{
		z -= deltaTime * movespeed;
		this->setPos(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('A'))
	{
		x -= deltaTime * movespeed;
		this->setPos(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('D'))
	{
		x += deltaTime * movespeed;
		this->setPos(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('Q'))
	{
		y -= deltaTime * movespeed;
		this->setPos(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('E'))
	{
		y += deltaTime * movespeed;
		this->setPos(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();
	Matrix4x4 temp;
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.m_x);
	worldCam = worldCam.multiplyMatrix(temp);

	temp.setRotationY(localRot.m_y);
	worldCam = worldCam.multiplyMatrix(temp);

	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.multiplyMatrix(temp);

	worldCam.inverse();
	this->localMatrix = worldCam;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point& mousePos)
{
	if (this->rmd)
	{
		Vector3D localRot = this->getLocalRotation();
		float x = localRot.m_x;
		float y = localRot.m_y;
		float z = localRot.m_z;

		float speed = 0.05f;
		x += mousePos.y * EngineTime::getDeltaTime() * speed;
		y += mousePos.x * EngineTime::getDeltaTime() * speed;

		this->setRot(x, y, z);

		this->updateViewMatrix();
	}
}

void Camera::onLMD(const Point& mousePos)
{
}

void Camera::onLMU(const Point& mousePos)
{
}

void Camera::onRMD(const Point& mousePos)
{
	this->rmd = true;
}

void Camera::onRMU(const Point& mousePos)
{
	this->rmd = false;
}
