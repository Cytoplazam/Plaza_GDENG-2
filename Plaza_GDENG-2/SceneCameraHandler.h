#pragma once
#include "Matrix4x4.h"
#include "Camera.h"
#include "EngineTime.h"

class SceneCameraHandler
{
public: 
	static SceneCameraHandler* get();
	static void init();
	static void destroy();

	void update();

	Matrix4x4 getSceneCameraViewMatrix();

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator = (SceneCameraHandler const&) {};
	static SceneCameraHandler* sharedInstance;
	Camera* sceneCamera;
};

