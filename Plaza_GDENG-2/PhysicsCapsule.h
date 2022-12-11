#pragma once

#include "GameObject.h"
#include "Capsule.h"
#include "VertexBuffer.h"
#include "VertexBufferTex.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "InputListener.h"
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "Texture.h"
#include "SceneCameraHandler.h"
#include "PhysicsComponent.h"
#include "GraphicsEngine.h"

class PhysicsCapsule : public Capsule
{
	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color1;
	};

public:
	PhysicsCapsule(string name, void* shaderByteCode, size_t sizeShader, float length, float radius, PrimitiveType type);
	~PhysicsCapsule();

	Vector3D Cyl(float u, float v);
	Vector3D SphA(float u, float v);
	Vector3D SphB(float u, float v);

	void update(float deltaTime) override;
	void draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right) override;
	void setAnimSpeed(float speed);

private:
	std::vector<vertex> vertexList;
	std::vector<unsigned int> indexList;

protected:
	VertexBuffer* vb;
	VertexBufferTex* vbt;
	Texture* tex;
	IndexBuffer* ib;
	ConstantBuffer* cb;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaScale = 1.0f;
	float scaleY = 1.0f;
	bool increasing = true;
	float deltaTime = 0.0f;
	float speed = 0.0f;
	float radius = 0.0f;
	float length = 0.0f;
	float pi = 3.14159265359;
	Matrix4x4 mWorldCam;
};

