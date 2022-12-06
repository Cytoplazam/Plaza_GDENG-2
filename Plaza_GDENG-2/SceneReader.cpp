#include "SceneReader.h"

SceneReader::SceneReader(string dir)
{
	this->dir = dir;
}

void SceneReader::readFromFile()
{
	string fileDir = this->dir + ".iet";
	if (this->dir.find(".iet") != std::string::npos)
	{
		fileDir = this->dir;
	}

	FileReader sceneFile;

	sceneFile.open(fileDir, std::ios::in);

	int index = 0;

	string readLine;

	string objectName;
	GameObject::PrimitiveType objectType;
	Vector3D pos;
	Vector3D rot;
	Vector3D scale;

	while (std::getline(sceneFile, readLine))
	{
		if (index == 0)
		{
			objectName = readLine;
			index++;
		}
		else if (index == 1)
		{
			/*std::vector stringSplit = StringUtils;
			index++;*/
		}
	}
}
