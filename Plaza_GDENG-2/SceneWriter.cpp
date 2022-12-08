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
	std::string fileDir = this->dir + ".xml";
	if (this->dir.find(".xml") != std::string::npos)
	{
		fileDir = this->dir;
	}

	FileWriter sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected Filename " << fileDir << "\n";

	GameObjectManager::List allObjects = GameObjectManager::get()->getAllObjects();

	sceneFile << "<GameObjects>" << std::endl;

	for (int i = 0; i < allObjects.size(); i++)
	{
		sceneFile << "<GameObject>" << std::endl;

		sceneFile << "<Name>" + allObjects[i]->getName() + "</Name>" << std::endl;
		Vector3D pos = allObjects[i]->getLocalPosition();
		Vector3D rot = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();

		
		sceneFile << "<Type>" << allObjects[i]->getType() << "</Type>" << std::endl;
		sceneFile << "<Position>" << std::endl;
		sceneFile << "<x>" << pos.m_x << "</x>" << std::endl;
		sceneFile << "<y>" << pos.m_y << "</y>" << std::endl;
		sceneFile << "<z>" << pos.m_z << "</z>" << std::endl;
		sceneFile << "</Position>" << std::endl;
		sceneFile << "<Rotation>" << std::endl;
		sceneFile << "<x>" << rot.m_x << "</x>" << std::endl;
		sceneFile << "<y>" << rot.m_y << "</y>" << std::endl;
		sceneFile << "<z>" << rot.m_z << "</z>" << std::endl;
		sceneFile << "</Rotation>" << std::endl;
		sceneFile << "<Scale>" << std::endl;
		sceneFile << "<x>" << scale.m_x << "</x>" << std::endl;
		sceneFile << "<y>" << scale.m_y << "</y>" << std::endl;
		sceneFile << "<z>" << scale.m_z << "</z>" << std::endl;
		sceneFile << "</Scale>" << std::endl;

		sceneFile << "</GameObject>" << std::endl;
	}

	sceneFile << "</GameObjects>" << std::endl;
	
	sceneFile.close();
}
