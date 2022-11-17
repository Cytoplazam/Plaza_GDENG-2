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
#include "SceneCameraHandler.h"

class Cube : public GameObject
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right) override;
	void setAnimSpeed(float speed);

private:
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

