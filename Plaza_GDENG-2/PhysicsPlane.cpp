#include "PhysicsPlane.h"

PhysicsPlane::PhysicsPlane(string name, void* shaderByteCode, size_t sizeShader): Cube(name, shaderByteCode, sizeShader, PrimitiveType::PPLANE)
{
	std::string path = "Assets/Textures/wood.jpg";
	std::wstring wPath = wstring(path.begin(), path.end());
	this->tex = TextureManager::get()->createTextureFromFile(wPath.c_str());

	if (!this->tex)
		std::cout << "no texture\n";
	else
		std::cout << "texture loaded\n";

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
	
	this->ComputeLocalMatrix();
	this->attachComponent(new PhysicsComponent(("PhysicsComponent"), this));

	PhysicsComponent* component = (PhysicsComponent*)this->findComponentByName("PhysicsComponent");

	component->getRigidBody()->setType(BodyType::KINEMATIC);
}

PhysicsPlane::~PhysicsPlane()
{
}
