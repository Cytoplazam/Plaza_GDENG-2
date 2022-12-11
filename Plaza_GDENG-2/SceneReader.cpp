#include "SceneReader.h"
#include "pugixml.hpp"
#include "pugiconfig.hpp"

using namespace pugi;

SceneReader::SceneReader(string dir)
{
	this->dir = dir;
}

SceneReader::~SceneReader()
{
}

void SceneReader::readFromFile()
{
	string fileDir = this->dir + ".xml";
	if (this->dir.find(".xml") != std::string::npos)
	{
		fileDir = this->dir;
	}

	xml_document doc;
	
	doc.load_file(fileDir.c_str());

	xml_node objs = doc.child("GameObjects").child("GameObject");

	string objectName;
	GameObject::PrimitiveType objectType;
	Vector3D pos;
	float posX;
	float posY;
	float posZ;
	Vector3D rot;
	float rotX;
	float rotY;
	float rotZ;
	Vector3D scale;
	float scaleX;
	float scaleY;
	float scaleZ;

	for (xml_node obj = objs; obj; obj = obj.next_sibling("GameObject"))
	{
		objectName = obj.child_value("Name");

		if (std::stoi(obj.child_value("Type")) == 1)
		{
			objectType = GameObject::PrimitiveType::CUBE;
		}
		if (std::stoi(obj.child_value("Type")) == 2)
		{
			objectType = GameObject::PrimitiveType::PCUBE;
		}
		if (std::stoi(obj.child_value("Type")) == 3)
		{
			objectType = GameObject::PrimitiveType::PLANE;
		}
		if (std::stoi(obj.child_value("Type")) == 4)
		{
			objectType = GameObject::PrimitiveType::PPLANE;
		}
		if (std::stoi(obj.child_value("Type")) == 5)
		{
			objectType = GameObject::PrimitiveType::SPHERE;
		}
		if (std::stoi(obj.child_value("Type")) == 6)
		{
			objectType = GameObject::PrimitiveType::PSPHERE;
		}
		if (std::stoi(obj.child_value("Type")) == 7)
		{
			objectType = GameObject::PrimitiveType::CAPSULE;
		}
		if (std::stoi(obj.child_value("Type")) == 8)
		{
			objectType = GameObject::PrimitiveType::PCAPSULE;
		}

		posX = std::stof(obj.child("Position").child_value("x"));
		posY = std::stof(obj.child("Position").child_value("y"));
		posZ = std::stof(obj.child("Position").child_value("z"));
		pos = Vector3D(posX, posY, posZ);

		rotX = std::stof(obj.child("Rotation").child_value("x"));
		rotY = std::stof(obj.child("Rotation").child_value("y"));
		rotZ = std::stof(obj.child("Rotation").child_value("z"));
		rot = Vector3D(rotX, rotY, rotZ);

		scaleX = std::stof(obj.child("Scale").child_value("x"));
		scaleY = std::stof(obj.child("Scale").child_value("y"));
		scaleZ = std::stof(obj.child("Scale").child_value("z"));
		scale = Vector3D(scaleX, scaleY, scaleZ);

		GameObjectManager::get()->createObjectFromFile(objectType, nullptr, 0, objectName, rot, pos, scale);
		std::cout << "Created " << objectName << " from file.\n";
	}
}
