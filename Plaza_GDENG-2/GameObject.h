#pragma once

#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "PixelShader.h"
#include "VertexShader.h"

using namespace std;

class VertexShader;
class PixelShader;

class GameObject
{
public:
	GameObject(string name);
	~GameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right) = 0;

	void setPos(float x, float y, float z);
	void setPos(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRot(float x, float y, float z);
	void setRot(Vector3D rot);
	Vector3D getLocalRotation();

	string getName();

	struct Vertex
	{
		Vector3D pos;
		Vector3D color;
		Vector3D color1;
	};

	_declspec(align(16))
		struct constant
	{
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projMatrix;
		unsigned int time;
	};

protected:
	VertexShader* vs;
	PixelShader* ps;
	Vector3D pos;
	Vector3D scale;
	Vector3D rot;
	string name;
};

