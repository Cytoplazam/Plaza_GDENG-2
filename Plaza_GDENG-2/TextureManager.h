#pragma once
#include <stdlib.h>
#include "Texture.h"
#include "ResourceManager.h"

class TextureManager: public ResourceManager
{
public:
	static void init();
	static void destroy();
	TextureManager();
	~TextureManager();
	static TextureManager* get();
	Texture* createTextureFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
private:
	static TextureManager* sharedInstance;
};

