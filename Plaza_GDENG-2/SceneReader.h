#pragma once

#include <string>
#include <vector>
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Vector3D.h"
#include <fstream>
#include <iostream>

using namespace std;

class SceneReader
{
public:
	SceneReader(string dir);
	~SceneReader();

	void readFromFile();
	
private:
	string dir;
};

