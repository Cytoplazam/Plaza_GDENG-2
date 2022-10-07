#pragma once
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DeviceContext.h"
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "EngineTime.h"
#include <iostream>

class Quad
{
public:
	Quad();

	void updateQuadPosition(float x, float y, float z, float width, float height);
	void draw(float x, float y, float z, float width, float height);

	~Quad();
private:
	VertexShader* m_vs;
	PixelShader* m_ps;
	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
private:
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;
	float m_delta_pos;
	float m_delta_scale;
	float ticks = 0.0f;
	double time = 0.0f;
	bool increasing = true;
};

