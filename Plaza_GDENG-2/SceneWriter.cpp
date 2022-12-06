#include "SceneWriter.h"

SceneWriter::SceneWriter(string dir)
{
	this->dir = dir;
}

SceneWriter::~SceneWriter()
{
}

void SceneWriter::WriteToFile()
{
	std::string fileDir = this->dir + ".iet";
	if (this->dir.find(".iet") != std::string::npos)
	{
		fileDir = this->dir;
	}

	FileWriter sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected Filename " << fileDir << "\n";

	GameObjectManager::List allObjects = GameObjectManager::get()->getAllObjects();

	for (int i = 0; i < allObjects.size(); i++)
	{
		sceneFile << allObjects[i]->getName() << std::endl;
		Vector3D pos = allObjects[i]->getLocalPosition();
		Vector3D rot = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();

		sceneFile << "Type: " << allObjects[i]->getType() << std::endl;
		sceneFile << "Position: " << pos.m_x << " " << pos.m_y << " " << pos.m_z << std::endl;
		sceneFile << "Rotation: " << rot.m_x << " " << rot.m_y << " " << rot.m_z << std::endl;
		sceneFile << "Scale: " << scale.m_x << " " << scale.m_y << " " << scale.m_z << std::endl;
	}
	
	sceneFile.close();
}
