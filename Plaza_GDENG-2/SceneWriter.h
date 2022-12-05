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
	/*static SceneWriter* get();
	static void init();
	static void destroy();*/

	SceneWriter();
	~SceneWriter();
	
	void WriteToFile();
private:
	static SceneWriter* sharedInstance;
	std::string dir;
};

