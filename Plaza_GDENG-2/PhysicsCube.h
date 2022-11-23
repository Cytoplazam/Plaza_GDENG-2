#pragma once

#include "Cube.h"

class PhysicsCube: public Cube
{
public:
	PhysicsCube(string name, void* shaderByteCode, size_t sizeShader);
	~PhysicsCube();
	void update(float deltaTime) override;
	void draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right) override;
private:
	float pos = 0.0f;
	float scale = 1.0f;
};

