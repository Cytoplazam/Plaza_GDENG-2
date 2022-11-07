#include "SceneCameraHandler.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;

SceneCameraHandler* SceneCameraHandler::get()
{
    return sharedInstance;
}

void SceneCameraHandler::init()
{
    sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
    delete sharedInstance;
}

void SceneCameraHandler::update()
{
    this->sceneCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
    return this->sceneCamera->getViewMatrix();
}

SceneCameraHandler::SceneCameraHandler()
{
    this->sceneCamera = new Camera("camera");
}

SceneCameraHandler::~SceneCameraHandler()
{
    delete sceneCamera;
}
