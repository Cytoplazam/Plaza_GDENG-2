#pragma once

#include <string>
#include <vector>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "PixelShader.h"
#include "Texture.h"
#include <string>
#include "VertexShader.h"
#include "AComponent.h"

using namespace std;

class VertexShader;
class PixelShader;
class Texture;

class AComponent;

class GameObject
{
public:
	enum PrimitiveType
	{
		CAMERA,
		CUBE, PCUBE, 
		PLANE, PPLANE,
		SPHERE, PSPHERE,
		CAPSULE, PCAPSULE,
		TEAPOT, BUNNY, ARMADILLO

	};

	typedef std::string String;
	typedef std::vector<AComponent*> ComponentList;

	GameObject(string name, PrimitiveType type);
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

	void changeName(string name);

	Vector3D getLocalRotation();

	PrimitiveType getType();

	void attachComponent(AComponent* component);

	AComponent* findComponentByName(String name);
	//AComponent* findComponentByType(AComponent::ComponentType type, String name);

	void ComputeLocalMatrix();

	Matrix4x4 getLocalMatrix();
	void setLocalMatrix(float matrix[16]);
	float* getPhysicsLocalMatrix();

	string getName();

	struct Vertex
	{
		Vector3D pos;
		Vector2D texcoord;
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
	ComponentList componentList;

	Matrix4x4 Summation;
	Matrix4x4 translate;
	Matrix4x4 ScaleMatrix;

	Matrix4x4 RotationZ;
	Matrix4x4 RotationF;
	Matrix4x4 RotationGl;
	Matrix4x4 RotationMatrix;

	Matrix4x4 RotationTotal;

	bool overrideMatrix = false;
	Matrix4x4 localMatrix;
	VertexShader* vs;
	PixelShader* ps;
	Texture* tex;
	Vector3D pos;
	Vector3D scale;
	Vector3D rot;
	string name;
	PrimitiveType type;
};

