#include "Cube.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "SwapChain.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader):GameObject(name)
{
	Vertex quadList[] =
	{
		//Front
		{Vector3D(-0.5f, -0.5f, -0.5f),  Vector3D(1, 0, 0),   Vector3D(0.2f, 0, 0)},
		{Vector3D(-0.5f, 0.5f, -0.5f),   Vector3D(1, 1, 0),   Vector3D(0.2f, 0.2f, 0)},
		{Vector3D(0.5f, 0.5f, -0.5f),    Vector3D(1, 1, 1),   Vector3D(0.2f, 0.2f, 0)},
		{Vector3D(0.5f, -0.5f, -0.5f),   Vector3D(1, 0, 0),   Vector3D(0.2f, 0, 0)},
		//Back
		{Vector3D(0.5f, -0.5f, 0.5f),    Vector3D(0, 1, 0),   Vector3D(0, 0.2f, 0)},
		{Vector3D(0.5f, 0.5f, 0.5f),     Vector3D(0, 1, 1),   Vector3D(0, 0.2f, 0.2f)},
		{Vector3D(-0.5f, 0.5f, 0.5f),    Vector3D(0, 1, 1),   Vector3D(1, 0.2f, 0.2f)},
		{Vector3D(-0.5f, -0.5f, 0.5f),   Vector3D(0, 1, 0),   Vector3D(0, 0.2f, 0)}
	};

	this->vb = GraphicsEngine::get()->createVertexBuffer();
	this->vb->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	unsigned int indexList[] =
	{
		//Front
		0, 1, 2, //First triangle
		2, 3, 0,
		//back
		4, 5, 6,
		6, 7, 4,
		//top
		1, 6, 5,
		5, 2, 1,
		//bottom
		7, 0, 3,
		3, 4, 7,
		//right
		3, 2, 5,
		5, 4, 3,
		//left
		7, 6, 1,
		1, 0, 7
	};

	this->ib = GraphicsEngine::get()->createIndexBuffer();
	this->ib->load(indexList, ARRAYSIZE(indexList));

	CBData cbData = {};
	cbData.time = 0;
	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cbData, sizeof(CBData));
}

Cube::~Cube()
{
	this->vb->release();
	this->ib->release();
	GameObject::~GameObject();
}

void Cube::update(float deltaTime)
{
	deltaPos += (this->deltaTime / 10.0f) * this->speed;

	this->setRot(deltaPos, deltaPos, deltaPos);
}

void Cube::draw(int w, int h, VertexShader* vs, PixelShader* ps)
{
	GraphicsEngine* ge = GraphicsEngine::get();
	DeviceContext* dc = ge->getImmediateDeviceContext();

	CBData cbData = {};

	if (this->deltaPos > 1.0f)
	{
		this->deltaPos = 0.0f;
	}
	else
	{
		this->deltaPos += this->deltaTime * 0.1f;
	}

	Matrix4x4 allMatrix;
	allMatrix.setIdentity();
	Matrix4x4 transMatrix;
	transMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix;
	scaleMatrix.setScale(this->getLocalScale());
	Vector3D rot;
	rot = this->getLocalRotation();
	Matrix4x4 zMatrix;
	Matrix4x4 xMatrix;
	Matrix4x4 yMatrix;
	zMatrix.setRotationZ(rot.m_z);
	xMatrix.setRotationX(rot.m_x);
	yMatrix.setRotationY(rot.m_y);

	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyMatrix(xMatrix.multiplyMatrix(yMatrix.multiplyMatrix(zMatrix)));
	allMatrix = allMatrix.multiplyMatrix(scaleMatrix.multiplyMatrix(rotMatrix));
	allMatrix = allMatrix.multiplyMatrix(transMatrix);
	cbData.worldMatrix = allMatrix;

	cbData.viewMatrix.setIdentity();
	cbData.projMatrix.setOrthoLH(w / 400.0f, h / 400.0f, -4.0f, 4.0f);
	
	this->cb->update(dc, &cbData);
	dc->setConstantBuffer(vs, this->cb);
	dc->setConstantBuffer(ps, this->cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	dc->setIndexBuffer(this->ib);
	dc->setVertexBuffer(this->vb);

	dc->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
