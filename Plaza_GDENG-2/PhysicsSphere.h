#pragma once

#include "GameObject.h"
#include "VertexBuffer.h"
#include "VertexBufferTex.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "InputListener.h"
#include "Matrix4x4.h"
#include "Texture.h"
#include "Sphere.h"
#include "SceneCameraHandler.h"
#include "PhysicsComponent.h"
#include "GraphicsEngine.h"

class PhysicsSphere : public Sphere
{
	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color1;
	};

public:
	PhysicsSphere(string name, void* shaderByteCode, size_t sizeShader, float radius, int stack, int sector, PrimitiveType type);
	~PhysicsSphere();

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
	Matrix4x4 mWorldCam;
};

