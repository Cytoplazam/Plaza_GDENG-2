#pragma once
#include <d3d11.h>
#include "TextureManager.h"
#include "MeshManager.h"

class SwapChain;
class DeviceContext;
class VertexBuffer;
class VertexBufferTex;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

class GraphicsEngine
{
public:
	GraphicsEngine();
	//initialize graphics engine and DX11 device
	bool init();
	//release all the loaded resources
	bool release();
	~GraphicsEngine();
public:
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();

	void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

	//DEFAULT SIMPLE SHADERS
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	ID3D11Device* getD3Ddevice();
	ID3D11DeviceContext* getContext();
	VertexBuffer* createVertexBuffer();
	VertexBufferTex* createVertexBufferTex();
	IndexBuffer* createIndexBuffer();
	ConstantBuffer* createConstantBuffer();
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
public:
	TextureManager* getTextureManager();
	MeshManager* getMeshmanager();
	//bool createShaders();
	//bool setShaders();
	//void getShaderBufferAndSize(void** bytecode, UINT* size);
public: 
	static GraphicsEngine* get();
private:
	DeviceContext* m_imm_device_context;
private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;
private:
	ID3DBlob* m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class VertexBufferTex;
	friend class VertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
	friend class IndexBuffer;
private:
	TextureManager* m_tex_manager = nullptr;
	MeshManager* m_mesh_manager = nullptr;

	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};

