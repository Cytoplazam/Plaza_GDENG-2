#include "Plane.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "SwapChain.h"
#include <iostream>

Plane::Plane(string name, void* shaderByteCode, size_t sizeShader, PrimitiveType type) :GameObject(name, PrimitiveType::PLANE)
{
	//mWorldCam.setTranslation(Vector3D(0, 1, -2));
	//this->ComputeLocalMatrix();
	//this->attachComponent(new PhysicsComponent(("PhysicsComponent"), this));
	std::string path = "Assets/Textures/wood.jpg";
	std::wstring wPath = wstring(path.begin(), path.end());
	this->tex = TextureManager::get()->createTextureFromFile(wPath.c_str());

	/*if (!this->tex)
		std::cout << "no texture\n";
	else
		std::cout << "texture loaded\n";*/

	Vector3D posList[] =
	{
		//Front
		{Vector3D(-0.5f, -0.5f, -0.5f)},
		{Vector3D(-0.5f, 0.5f, -0.5f)},
		{Vector3D(0.5f, 0.5f, -0.5f)},
		{Vector3D(0.5f, -0.5f, -0.5f)},
		//Back
		{Vector3D(0.5f, -0.5f, 0.5f)},
		{Vector3D(0.5f, 0.5f, 0.5f)},
		{Vector3D(-0.5f, 0.5f, 0.5f)},
		{Vector3D(-0.5f, -0.5f, 0.5f)}
	};

	Vector2D texCoordList[] =
	{
		//Front
		{Vector2D(0.0f, 0.0f)},
		{Vector2D(0.0f, 1.0f)},
		{Vector2D(1.0f, 0.0f)},
		{Vector2D(1.0f, 1.0f)},
	};

	//Vertex quadList[] =
	//{
	//	//Front
	//	{Vector3D(-0.5f, -0.5f, -0.5f),  Vector3D(1, 0, 0),   Vector3D(1, 0, 0)},
	//	{Vector3D(-0.5f, 0.5f, -0.5f),   Vector3D(0, 1, 0),   Vector3D(0, 1, 0)},
	//	{Vector3D(0.5f, 0.5f, -0.5f),    Vector3D(0, 0, 1),   Vector3D(0, 0, 1)},
	//	{Vector3D(0.5f, -0.5f, -0.5f),   Vector3D(1, 1, 0),   Vector3D(1, 1, 0)},
	//	//Back
	//	{Vector3D(0.5f, -0.5f, 0.5f),    Vector3D(1, 0, 0),   Vector3D(1, 0, 0)},
	//	{Vector3D(0.5f, 0.5f, 0.5f),     Vector3D(0, 1, 0),   Vector3D(0, 1, 0)},
	//	{Vector3D(-0.5f, 0.5f, 0.5f),    Vector3D(0, 0, 1),   Vector3D(0, 0, 1)},
	//	{Vector3D(-0.5f, -0.5f, 0.5f),   Vector3D(1, 1, 0),   Vector3D(1, 1, 0)}
	//};

	Vertex quadList[] =
	{
		//Front
		{posList[0], texCoordList[1]},
		{posList[1], texCoordList[0]},
		{posList[2], texCoordList[2]},
		{posList[3], texCoordList[3]},
		//Back
		{posList[4], texCoordList[1]},
		{posList[5], texCoordList[0]},
		{posList[6], texCoordList[2]},
		{posList[7], texCoordList[3]},

		{posList[1], texCoordList[1]},
		{posList[6], texCoordList[0]},
		{posList[5], texCoordList[2]},
		{posList[2], texCoordList[3]},

		{posList[7], texCoordList[1]},
		{posList[0], texCoordList[0]},
		{posList[3], texCoordList[2]},
		{posList[4], texCoordList[3]},

		{posList[3], texCoordList[1]},
		{posList[2], texCoordList[0]},
		{posList[5], texCoordList[2]},
		{posList[4], texCoordList[3]},

		{posList[7], texCoordList[1]},
		{posList[6], texCoordList[0]},
		{posList[1], texCoordList[2]},
		{posList[0], texCoordList[3]}
	};

	this->vbt = GraphicsEngine::get()->createVertexBufferTex();
	this->vbt->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	unsigned int indexList[] =
	{
		//Front
		0, 1, 2, //First triangle
		2, 3, 0,
		//back
		4, 5, 6,
		6, 7, 4,
		//top
		8, 9, 10,
		10, 11, 8,
		//bottom
		12, 13, 14,
		14, 15, 12,
		//right
		16, 17, 18,
		18, 19, 16,
		//left
		20, 21, 22,
		22, 23, 20
	};

	this->ib = GraphicsEngine::get()->createIndexBuffer();
	this->ib->load(indexList, ARRAYSIZE(indexList));

	constant cbData;
	cbData.time = 0;
	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cbData, sizeof(constant));

	this->setPos(Vector3D(0.0f, -5.0f, 3.0f));
	this->setScale(Vector3D(50.0f, 1.0f, 50.0f));
}

Plane::~Plane()
{
	this->cb->release();
	this->vbt->release();
	this->ib->release();
	GameObject::~GameObject();
}

void Plane::update(float deltaTime)
{
	deltaPos += (deltaTime / 10.0f) * this->speed;

	//this->setRot(deltaPos, deltaPos, deltaPos);
}

void Plane::draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right)
{
	constant cbData;

	Matrix4x4 temp;
	Matrix4x4 worldCam;

	cbData.worldMatrix.setIdentity();
	worldCam.setIdentity();

	/*if (this->deltaPos > 1.0f)
	{
		this->deltaPos = 0.0f;
	}
	else
	{
		this->deltaPos += this->deltaTime * 0.1f;
	}*/

	Matrix4x4 allMatrix;
	allMatrix.setIdentity();
	Matrix4x4 transMatrix;
	transMatrix.setIdentity();
	transMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(this->getLocalScale());
	Vector3D rot;
	rot = this->getLocalRotation();
	Matrix4x4 zMatrix;
	Matrix4x4 xMatrix;
	Matrix4x4 yMatrix;
	zMatrix.setIdentity();
	zMatrix.setRotationZ(rot.m_z);
	xMatrix.setIdentity();
	xMatrix.setRotationX(rot.m_x);
	yMatrix.setIdentity();
	yMatrix.setRotationY(rot.m_y);

	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyMatrix(xMatrix.multiplyMatrix(yMatrix.multiplyMatrix(zMatrix)));
	allMatrix = allMatrix.multiplyMatrix(scaleMatrix.multiplyMatrix(rotMatrix));
	allMatrix = allMatrix.multiplyMatrix(transMatrix);
	cbData.worldMatrix = allMatrix;

	Matrix4x4 camMatrix = SceneCameraHandler::get()->getSceneCameraViewMatrix();
	cbData.viewMatrix = camMatrix;

	/*temp.setIdentity();
	temp.setRotationX(rot.m_x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(rot.m_y);
	worldCam *= temp;

	Vector3D newPos = mWorldCam.getTranslation() + worldCam.getZDirection() * (forward * 0.3f);

	newPos = newPos + worldCam.getXDirection() * (right * 0.3f);

	worldCam.setTranslation(Vector3D(newPos));

	mWorldCam = worldCam;
	worldCam.inverse();

	cbData.viewMatrix = worldCam;
	cbData.projMatrix.setOrthoLH(w / 400.0f, h / 400.0f, -4.0f, 4.0f);*/

	cbData.projMatrix.setPerspectiveFovLH(1.57f, float(w) / float(h), 0.1f, 100.0f);

	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cbData);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, this->cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, this->cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setTexture(vs, this->tex);
	GraphicsEngine::get()->getImmediateDeviceContext()->setTexture(ps, this->tex);

	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBufferTex(this->vbt);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

void Plane::setAnimSpeed(float speed)
{
	this->speed = speed;
}
