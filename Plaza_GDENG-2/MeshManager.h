#pragma once
#include "ResourceManager.h"
#include "Mesh.h"

class MeshManager: public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	static void init();
	static void destroy();
	static MeshManager* get();
	Mesh* createMeshFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
private:
	static MeshManager* sharedInstance;
};

