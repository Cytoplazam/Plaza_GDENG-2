#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "GameObjectManager.h"

using namespace std;

typedef std::fstream FileWriter;

class SceneWriter
{
public:
	SceneWriter(string dir);
	~SceneWriter();
	
	void WriteToFile();

private:
	string dir;
};

