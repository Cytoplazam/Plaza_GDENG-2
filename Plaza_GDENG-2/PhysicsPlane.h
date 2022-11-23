#pragma once
#include "Cube.h"
#include "TextureManager.h"
#include "GraphicsEngine.h"

class PhysicsPlane: public Cube
{
public:
	PhysicsPlane(string name, void* shaderByteCode, size_t sizeShader);
	~PhysicsPlane();
private:
	float pos = 0.0f;
	float scale = 1.0f;
};

