#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Quad.h"
#include "Cube.h"
#include "PhysicsCube.h"
#include "Plane.h"
#include "PhysicsPlane.h"
#include "OBJ.h"
#include "OBJa.h"
#include "OBJb.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "Texture.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "UIManager.h"
#include <iostream>
#include <vector>

class AppWindow: public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mousePos) override;

	virtual void onLMD(const Point& mousePos) override;
	virtual void onLMU(const Point& mousePos) override;

	virtual void onRMD(const Point& mousePos) override;
	virtual void onRMU(const Point& mousePos) override;
public:
	typedef std::wstring String;
	const String WOOD = L"Assets\\Textures\\wood.jpg";
private:
	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
private:
	float scale = 1.0f;
	float rotX = 0.0f;
	float rotY = 0.0f;
	float ticks = 0.0f;
	float forward = 0.0f;
	float right = 0.0f;
	std::vector<Cube*> cubes;
	std::vector<PhysicsCube*> pCubes;
	std::vector<Plane*> planes;
	std::vector<PhysicsPlane*> pPlanes;
	std::vector<OBJ*> objs;
	std::vector<OBJa*> objas;
	std::vector<OBJb*> objbs;
	InputSystem is;
	SwapChain* m_swap_chain;
	Texture* m_wood_tex;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	VertexShader* m_vst;
	PixelShader* m_pst;
	ConstantBuffer* m_cb;
	/*Plane* plane;
	Cube* cube;
	PhysicsCube* pCube;
	OBJ* obj;
	OBJa* obja;
	OBJb* objb;
	Quad* quad[];*/
};

