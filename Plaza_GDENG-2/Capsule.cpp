#include "Capsule.h"

Capsule::Capsule(string name, void* shaderByteCode, size_t sizeShader, float length, float radius, PrimitiveType type) :GameObject(name, PrimitiveType::CAPSULE)
{
	std::string path = "Assets/Textures/wall.jpg";
	std::wstring wPath = wstring(path.begin(), path.end());
	this->tex = TextureManager::get()->createTextureFromFile(wPath.c_str());

	this->radius = radius;
	this->length = length;
	float res = 24;

	Vector3D start = Vector3D(0, 0, 0);
	Vector3D end = Vector3D(1, 1, 1);

	Vector3D step = (end - start) / res;
	
	for (float i = 0; i < res; i++)
	{
		for (float j = 0; j < res; j++)
		{
			float u = i * step.m_x + start.m_x;
			float v = j * step.m_y + start.m_y;

			float un = 0;
			float vn = 0;

			if (i + 1 == res)
				un = end.m_x;
			else
				un = (i + 1) * step.m_x + start.m_x;

			if (j + 1 == res)
				vn = end.m_y;
			else
				vn = (j + 1) * step.m_y + start.m_y;

			int verts = this->vertexList.size();
			vertex v0 = { this->Cyl(u, v), Vector3D((float)i / res, (float)j / res, 0), Vector3D(0.2f, 0, 0) };
			vertex v1 = { this->Cyl(u, vn), Vector3D((float)i / res, (float)j + 1 / res, 0), Vector3D(0.2f, 0, 0) };
			vertex v2 = { this->Cyl(un, v), Vector3D((float)i + 1 / res, (float)j / res, 0), Vector3D(0.2f, 0, 0) };
			vertex v3 = { this->Cyl(un, vn), Vector3D((float)i + 1 / res, (float)j + 1 / res, 0), Vector3D(0.2f, 0, 0) };

			this->vertexList.push_back(v0);
			this->vertexList.push_back(v1);
			this->vertexList.push_back(v2);
			this->vertexList.push_back(v3);
			
			this->indexList.push_back(verts);
			this->indexList.push_back(verts + 2);
			this->indexList.push_back(verts + 1);
			this->indexList.push_back(verts + 3);
			this->indexList.push_back(verts + 1);
			this->indexList.push_back(verts + 2);

			verts = this->vertexList.size();
			v0 = { this->SphA(u, v), Vector3D((float)i / res, (float)j / res, 0), Vector3D(0.2f, 0, 0) };
			v1 = { this->SphA(u, vn), Vector3D((float)i / res, (float)j + 1 / res, 0), Vector3D(0.2f, 0, 0) };
			v2 = { this->SphA(un, v), Vector3D((float)i + 1 / res, (float)j / res, 0), Vector3D(0.2f, 0, 0) };
			v3 = { this->SphA(un, vn), Vector3D((float)i + 1 / res, (float)j + 1 / res, 0), Vector3D(0.2f, 0, 0) };

			this->vertexList.push_back(v0);
			this->vertexList.push_back(v1);
			this->vertexList.push_back(v2);
			this->vertexList.push_back(v3);

			this->indexList.push_back(verts);
			this->indexList.push_back(verts + 2);
			this->indexList.push_back(verts + 1);
			this->indexList.push_back(verts + 3);
			this->indexList.push_back(verts + 1);
			this->indexList.push_back(verts + 2);

			verts = this->vertexList.size();
			v0 = { this->SphB(u, v), Vector3D((float)i / res, (float)j / res, 0), Vector3D(0.2f, 0, 0) };
			v1 = { this->SphB(u, vn), Vector3D((float)i / res, (float)j + 1 / res, 0), Vector3D(0.2f, 0, 0) };
			v2 = { this->SphB(un, v), Vector3D((float)i + 1 / res, (float)j / res, 0), Vector3D(0.2f, 0, 0) };
			v3 = { this->SphB(un, vn), Vector3D((float)i + 1 / res, (float)j + 1 / res, 0), Vector3D(0.2f, 0, 0) };

			this->vertexList.push_back(v0);
			this->vertexList.push_back(v1);
			this->vertexList.push_back(v2);
			this->vertexList.push_back(v3);

			this->indexList.push_back(verts);
			this->indexList.push_back(verts + 2);
			this->indexList.push_back(verts + 1);
			this->indexList.push_back(verts + 3);
			this->indexList.push_back(verts + 1);
			this->indexList.push_back(verts + 2);
		}
	}

	this->vbt = GraphicsEngine::get()->createVertexBufferTex();
	this->vbt->load(&(this->vertexList[0]), sizeof(vertex), this->vertexList.size(), shaderByteCode, sizeShader);

	this->ib = GraphicsEngine::get()->createIndexBuffer();
	this->ib->load(&(this->indexList[0]), indexList.size());

	constant cbData;
	cbData.time = 0;
	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cbData, sizeof(constant));
}

Capsule::~Capsule()
{
	this->cb->release();
	this->vbt->release();
	this->ib->release();
	GameObject::~GameObject();
}

Vector3D Capsule::Cyl(float u, float v)
{
	u = 2.0f * this->pi * u;

	Vector3D x = Vector3D(1, 0, 0);
	Vector3D y = Vector3D(0, 1, 0);
	Vector3D z = Vector3D(0, 0, 1);

	Vector3D end = Vector3D(0, 0, 0);

	return end + z * cosf(u) * this->radius + x * sinf(u) * this->radius + y * v * this->length;
}

Vector3D Capsule::SphA(float u, float v)
{
	u = 2.0f * this->pi * u;
	v = (pi / 2.0f) * v;

	Vector3D x = Vector3D(1, 0, 0);
	Vector3D y = Vector3D(0, 1, 0);
	Vector3D z = Vector3D(0, 0, 1);

	Vector3D top = Vector3D(0, this->length, 0);

	return top + z * cosf(u) * cosf(v) * this->radius + x * sinf(u) * cosf(v) * this->radius + y * sinf(v) * this->radius;
}

Vector3D Capsule::SphB(float u, float v)
{
	u = 2.0f * this->pi * u;
	v = (pi / 2.0f) * (v - 1);

	Vector3D x = Vector3D(1, 0, 0);
	Vector3D y = Vector3D(0, 1, 0);
	Vector3D z = Vector3D(0, 0, 1);

	Vector3D end = Vector3D(0, 0, 0);

	return end + z * cosf(u) * cosf(v) * this->radius + x * sinf(u) * cosf(v) * this->radius + y * sinf(v) * this->radius;
}

void Capsule::update(float deltaTime)
{
}

void Capsule::draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right)
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

void Capsule::setAnimSpeed(float speed)
{
}
