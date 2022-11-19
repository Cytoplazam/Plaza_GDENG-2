#pragma once

#include "GameObject.h"
#include "VertexBuffer.h"
#include "VertexBufferTex.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "InputListener.h"
#include "Matrix4x4.h"
#include "SceneCameraHandler.h"
#include "Mesh.h"
#include "Texture.h"
#include "MeshManager.h"

class OBJ : public GameObject
{
public:
	OBJ(string name, void* shaderByteCode, size_t sizeShader);
	~OBJ();

	void update(float deltaTime) override;
	void draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right) override;
	void setAnimSpeed(float speed);

private:
	VertexBuffer* vb;
	VertexBufferTex* vbt;
	Texture* tex;
	IndexBuffer* ib;
	Mesh* m_mesh;
	ConstantBuffer* cb;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaScale = 1.0f;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;
	bool increasing = false;
	float deltaTime = 0.0f;
	float speed = 0.0f;
	Matrix4x4 mWorldCam;
};

