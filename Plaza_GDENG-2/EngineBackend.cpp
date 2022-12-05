#include "EngineBackend.h"
#include <iostream>

EngineBackend* EngineBackend::sharedInstance = NULL;

EngineBackend* EngineBackend::get()
{
    return sharedInstance;
}

void EngineBackend::init()
{
    sharedInstance = new EngineBackend();
}

void EngineBackend::destroy()
{
    delete sharedInstance;
}

void EngineBackend::setMode(EditorMode mode)
{
    this->editorMode = mode;
    
    if (this->editorMode == EditorMode::PLAY)
    {
        //GameObjectManager::get()->
    }
    else if (this->editorMode == EditorMode::EDITOR)
    {

    }
}

void EngineBackend::startFrameStep()
{
}

void EngineBackend::endFrameStep()
{
}

bool EngineBackend::insideFrameStep()
{
    return false;
}

EngineBackend::EngineBackend()
{
}

EngineBackend::~EngineBackend()
{
}
