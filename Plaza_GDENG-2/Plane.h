#pragma once

#include "GameObject.h"
#include "VertexBuffer.h"
#include "VertexBufferTex.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "PhysicsComponent.h"

class Plane : public GameObject
{
public:
	Plane(string name, void* shaderByteCode, size_t sizeShader);
	~Plane();

	void update(float deltaTime) override;
	void draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right) override;
	void setAnimSpeed(float speed);

private:
	VertexBuffer* vb;
	VertexBufferTex* vbt;
	IndexBuffer* ib;
	ConstantBuffer* cb;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 0.0f;
	Matrix4x4 mWorldCam;
};

