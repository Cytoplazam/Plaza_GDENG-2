#include "Sphere.h"

Sphere::Sphere(string name, void* shaderByteCode, size_t sizeShader, float radius, int stack, int sector, PrimitiveType type) :GameObject(name, PrimitiveType::SPHERE)
{
	float x;
	float y;
	float z;
	float xy;
	float pi = 3.14159265359;
	float stackStep = 2 * pi / float(stack);
	float sectorStep = 2 * pi / float(sector);
	float stackAngle;
	float sectorAngle;

	std::string path = "Assets/Textures/grass.jpg";
	std::wstring wPath = wstring(path.begin(), path.end());
	this->tex = TextureManager::get()->createTextureFromFile(wPath.c_str());

	for (int i = 0; i <= stack; i++)
	{
		stackAngle = pi / 2.0f - i * stackStep;
		xy = radius * cosf(stackAngle);
		y = radius * sinf(stackAngle);

		for (int j = 0; j <= sector; j++)
		{
			sectorAngle = j * sectorStep;
			z = xy * cosf(sectorAngle);
			x = xy * sinf(sectorAngle);


			vertex vertSector = { Vector3D(x, y, z), Vector3D(1, 0, 0), Vector3D(0, 1, 0) };

			this->vertexList.push_back(vertSector);
		}
	}

	this->vbt = GraphicsEngine::get()->createVertexBufferTex();
	this->vbt->load(&(this->vertexList[0]), sizeof(vertex), this->vertexList.size(), shaderByteCode, sizeShader);

	int k1, k2;

	for (int i = 0; i < stack; i++)
	{
		k1 = i * (sector + 1);
		k2 = k1 + sector + 1;

		for (int j = 0; j < sector; j++)
		{
			if (i != 0)
			{
				this->indexList.push_back(k1);
				this->indexList.push_back(k1 + 1);
				this->indexList.push_back(k2);
			}

			if (i != (stack - 1))
			{
				this->indexList.push_back(k1 + 1);
				this->indexList.push_back(k2 + 1);
				this->indexList.push_back(k2);
			}

			k1++;
			k2++;
		}
	}

	this->ib = GraphicsEngine::get()->createIndexBuffer();
	this->ib->load(&(this->indexList[0]), indexList.size());

	constant cbData;
	cbData.time = 0;
	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cbData, sizeof(constant));
}

Sphere::~Sphere()
{
	this->cb->release();
	this->vbt->release();
	this->ib->release();
	GameObject::~GameObject();
}

void Sphere::update(float deltaTime)
{
}

void Sphere::draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right)
{
	constant cbData;

	if (this->overrideMatrix)
	{
		cbData.worldMatrix = this->getLocalMatrix();
	}
	else
	{
		this->ComputeLocalMatrix();
		cbData.worldMatrix = this->getLocalMatrix();
	}

	Matrix4x4 temp;
	Matrix4x4 worldCam;

	Matrix4x4 camMatrix = SceneCameraHandler::get()->getSceneCameraViewMatrix();
	cbData.viewMatrix = camMatrix;

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

void Sphere::setAnimSpeed(float speed)
{
}
