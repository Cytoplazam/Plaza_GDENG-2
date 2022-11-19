#include "AppWindow.h"
#include "InputSystem.h"
#include <Windows.h>
#include <cstdlib>

/*vec3
{
	float x, y, z;
};*/

/*struct vertex
{
	vec3 position; 
	vec3 position1;
	vec3 color;
	vec3 color1;
};*/

__declspec(align(16))
struct constant
{
	unsigned int m_time;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
	GraphicsEngine::get()->releaseCompiledShader();
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::get()->addListener(this);
	TextureManager::init();
	MeshManager::init();
	//m_wood_tex = TextureManager::get()->createTextureFromFile(WOOD.c_str());
	EngineTime::initialize();
	GraphicsEngine::get()->init();
	SceneCameraHandler::init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();

	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	/*vertex list[] =
	{
		//RAINBOW TRIANGLE
		//{-0.5f, -0.5f, 0.0f, 1, 0, 0},
		//{0.0f, 0.5f, 0.0f, 0, 1, 0},
		//{0.5f, -0.5f, 0.0f, 0, 0, 1}

		//RAINBOW RECTANGLE
		//Triangle List
		{-0.5f, -0.5f, 0.0f, -0.32f, -0.11f, 0.0f,  0, 0, 0,   0, 1, 0},
		{-0.5f, 0.5f, 0.0f,  -0.11f, 0.78f, 0.0f,   1, 1, 0,   0, 1, 1},
		{0.5f, -0.5f, 0.0f,  0.75f, -0.73f, 0.0f,   0, 0, 1,   1, 0, 0},
		{0.5f, 0.5f, 0.0f,   0.88f, 0.7f, 0.0f,     1, 1, 1,   0, 0, 1}

		//GREEN RECTANGLE
		//Triangle List
		//{-0.5f, -0.5f, 0.0f, 0, 1, 0},
		//{-0.5f, 0.5f, 0.0f, 0, 1, 0},
		//{0.5f, -0.5f, 0.0f, 0, 1, 0},
		//{0.5f, 0.5f, 0.0f, 0, 1, 0}


		/*Triangle Strip x - y - z
		{-0.5f, -0.5f, 0.0f}, //pos1
		{-0.5f, 0.5f, 0.0f}, //pos2
		{0.5f, 0.5f, 0.0f}, //pos3
		{0.5f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{-0.5f, -0.5f, 0.0f}
	};*/

	//m_vb = GraphicsEngine::get()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(list);

	//GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	/*for (int i = 1; i <= 3; i++)
	{
		this->quad[i] = new Quad();
	}*/


	/*GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);*/

	GraphicsEngine::get()->compileVertexShader(L"VertexShaderTex.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vst = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	//m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	//srand(time(NULL));
	for (int i = 0; i < 1; i++)
	{
		//float x = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
		//float y = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
		//float z = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;

		Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);
		//cubeObject->setAnimSpeed(float(rand()) / float(RAND_MAX) * (3.75f - -3.75f) + -3.75f);
		/*if (i == 0)
			cubeObject->setPos(Vector3D(0, 0.9f, 0));
		else if (i == 1)
			cubeObject->setPos(Vector3D(-1.5f, 2.0f, 0));
		else if (i == 2)
			cubeObject->setPos(Vector3D(-1.5f, 3.0f, -2.0f));*/
		cubeObject->setPos(Vector3D(0.0f, 0.0f, 3.0f));
		cubeObject->setRot(Vector3D(0.0f, 0.0f, 0.0f));
		cubeObject->setScale(Vector3D(0.01f, 0.01f, 0.01f));
		this->cubes.push_back(cubeObject);
	}

	for (int i = 0; i < 1; i++)
	{
		//float x = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
		//float y = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
		//float z = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;

		OBJ* objobj = new OBJ("OBJ", shader_byte_code, size_shader);
		//cubeObject->setAnimSpeed(float(rand()) / float(RAND_MAX) * (3.75f - -3.75f) + -3.75f);
		/*if (i == 0)
			cubeObject->setPos(Vector3D(0, 0.9f, 0));
		else if (i == 1)
			cubeObject->setPos(Vector3D(-1.5f, 2.0f, 0));
		else if (i == 2)
			cubeObject->setPos(Vector3D(-1.5f, 3.0f, -2.0f));*/
		objobj->setPos(Vector3D(0.0f, 0.0f, 3.0f));
		objobj->setRot(Vector3D(0.0f, 0.0f, 0.0f));
		objobj->setScale(Vector3D(1.0f, 1.0f, 1.0f));
		this->objs.push_back(objobj);
	}

	for (int i = 0; i < 1; i++)
	{
		//float x = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
		//float y = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
		//float z = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;

		OBJa* objobj = new OBJa("OBJa", shader_byte_code, size_shader);
		//cubeObject->setAnimSpeed(float(rand()) / float(RAND_MAX) * (3.75f - -3.75f) + -3.75f);
		/*if (i == 0)
			cubeObject->setPos(Vector3D(0, 0.9f, 0));
		else if (i == 1)
			cubeObject->setPos(Vector3D(-1.5f, 2.0f, 0));
		else if (i == 2)
			cubeObject->setPos(Vector3D(-1.5f, 3.0f, -2.0f));*/
		objobj->setPos(Vector3D(-5.0f, 0.0f, 3.0f));
		objobj->setRot(Vector3D(0.0f, 0.0f, 0.0f));
		objobj->setScale(Vector3D(1.0f, 1.0f, 1.0f));
		this->objas.push_back(objobj);
	}

	for (int i = 0; i < 1; i++)
	{
		//float x = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
		//float y = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;
		//float z = float(rand()) / float(RAND_MAX) * (5.0f - -5.0f) + -5.0f;

		OBJb* objobj = new OBJb("OBJb", shader_byte_code, size_shader);
		//cubeObject->setAnimSpeed(float(rand()) / float(RAND_MAX) * (3.75f - -3.75f) + -3.75f);
		/*if (i == 0)
			cubeObject->setPos(Vector3D(0, 0.9f, 0));
		else if (i == 1)
			cubeObject->setPos(Vector3D(-1.5f, 2.0f, 0));
		else if (i == 2)
			cubeObject->setPos(Vector3D(-1.5f, 3.0f, -2.0f));*/
		objobj->setPos(Vector3D(5.0f, 0.0f, 3.0f));
		objobj->setRot(Vector3D(0.0f, 0.0f, 0.0f));
		objobj->setScale(Vector3D(1.0f, 1.0f, 1.0f));
		this->objbs.push_back(objobj);
	}
	for (int i = 0; i < 1; i++)
	{
		Plane* plane = new Plane("Plane", shader_byte_code, size_shader);
		/*if (i == 0)
		{
			plane->setPos(Vector3D(0.0f, 0.0f, 0.0f));
			plane->setRot(Vector3D(0, 0, 90));
		}
		if (i == 1)
		{
			plane->setPos(Vector3D(-1.55f, 0.0f, 0.0f));
			plane->setRot(Vector3D(0, 0, -90));
		}
		if (i == 2)
		{
			plane->setPos(Vector3D(1.55f, 0.0f, 0.0f));
			plane->setRot(Vector3D(0, 0, -90));
		}
		if (i == 3)
		{
			plane->setPos(Vector3D(3.1f, 0.0f, 0.0f));
			plane->setRot(Vector3D(0, 0, 90));
		}
		if (i == 4)
		{
			plane->setPos(Vector3D(4.65f, 0.0f, 0.0f));
			plane->setRot(Vector3D(0, 0, -90));
		}
		if (i == 5)
		{
			plane->setPos(Vector3D(6.2f, 0.0f, 0.0f));
			plane->setRot(Vector3D(0, 0, 90));
		}
		if (i == 6)
		{
			plane->setPos(Vector3D(0.55f, 1.55f, 0.0f));
			plane->setRot(Vector3D(0, 0, 0));
		}
		if (i == 7)
		{
			plane->setPos(Vector3D(4.1f, 1.55f, 0.0f));
			plane->setRot(Vector3D(0, 0, 0));
		}
		if (i == 8)
		{
			plane->setPos(Vector3D(1.55f, 3.12f, 0.0f));
			plane->setRot(Vector3D(0, 0, 90));
		}
		if (i == 9)
		{
			plane->setPos(Vector3D(0.0f, 3.12f, 0.0f));
			plane->setRot(Vector3D(0, 0, -90));
		}
		if (i == 10)
		{
			plane->setPos(Vector3D(3.1f, 3.12f, 0.0f));
			plane->setRot(Vector3D(0, 0, -90));
		}
		if (i == 11)
		{
			plane->setPos(Vector3D(4.65f, 3.12f, 0.0f));
			plane->setRot(Vector3D(0, 0, 90));
		}
		if (i == 12)
		{
			plane->setPos(Vector3D(2.32f, 4.7f, 0.0f));
			plane->setRot(Vector3D(0, 0, 0));
		}
		if (i == 13)
		{
			plane->setPos(Vector3D(1.55f, 6.24f, 0.0f));
			plane->setRot(Vector3D(0, 0, -90));
		}
		if (i == 14)
		{
			plane->setPos(Vector3D(3.1f, 6.24f, 0.0f));
			plane->setRot(Vector3D(0, 0, 90));
		}*/
		plane->setPos(Vector3D(0.0f, -0.5f, 3.0f));
		plane->setRot(Vector3D(rotX, rotY, 0.0f));
		plane->setScale(Vector3D(5.0f, 0.01f, 5.0f));
		this->planes.push_back(plane);
	}

	//GraphicsEngine::get()->releaseCompiledShader();

	/*GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);*/

	GraphicsEngine::get()->compilePixelShader(L"PixelShaderTex.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_pst = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;

	//GraphicsEngine::get()->releaseCompiledShader();

	//constant cc;

	//cc.m_time = 0;
	UIManager::get()->init(m_hwnd);
	//m_cb = GraphicsEngine::get()->createConstantBuffer();
	//m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	this->ticks += EngineTime::getDeltaTime();
	Window::onUpdate();
	InputSystem::get()->update();
	//InputSystem::get()->showCursor(false);
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0, 0.5, 1);

	RECT rc = this->getClientWindowRect();
	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);
	
	//quad[1]->draw(x, y, 0, width / 300.0f, height / 300.0f, scaleX, scaleY);
	//quad[2]->draw(0.5, 0.5, 0, width / 400.0f, height / 400.0f);
	//quad[3]->draw(-0.5, -0.5, 0, width / 400.0f, height / 400.0f);
	
	/*if (GetKeyState('W') & 0x8000)
		y = is.translateYP(y);
	if (GetKeyState('S') & 0x8000)
		y = is.translateYN(y);
	if (GetKeyState('D') & 0x8000)
		x = is.translateXP(x);
	if (GetKeyState('A') & 0x8000)
		x = is.translateXN(x);
	if (GetKeyState('E') & 0x8000)
		scaleX = is.scaleXN(scaleX);
	if (GetKeyState('R') & 0x8000)
		scaleX = is.scaleXP(scaleX);
	if (GetKeyState('T') & 0x8000)
		scaleY = is.scaleYN(scaleY);
	if (GetKeyState('Y') & 0x8000)
		scaleY = is.scaleYP(scaleY);*/

	//constant cc;
	//cc.m_time = ::GetTickCount	();
	//m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//GraphicsEngine::get()->setShaders();
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	for (int i = 0; i < this->cubes.size(); i++)
	{
		//this->cubes[i]->setScale(Vector3D(scale, scale, scale));
		//this->cubes[i]->setRot(Vector3D(rotX, rotY, 0.0f));
		//this->cubes[i]->setAnimSpeed(1.0f);
		//this->cubes[i]->update(EngineTime::getDeltaTime());
		//this->cubes[i]->draw(width, height, this->m_vst, this->m_pst, forward, right);
	}

	for (int i = 0; i < this->objs.size(); i++)
	{
		//this->cubes[i]->setScale(Vector3D(scale, scale, scale));
		//this->cubes[i]->setRot(Vector3D(rotX, rotY, 0.0f));
		//this->objs[i]->setAnimSpeed(1.0f);
		//this->objs[i]->update(EngineTime::getDeltaTime());
		this->objs[i]->draw(width, height, this->m_vst, this->m_pst, forward, right);
	}

	for (int i = 0; i < this->objas.size(); i++)
	{
		//this->cubes[i]->setScale(Vector3D(scale, scale, scale));
		//this->cubes[i]->setRot(Vector3D(rotX, rotY, 0.0f));
		//this->objs[i]->setAnimSpeed(1.0f);
		//this->objs[i]->update(EngineTime::getDeltaTime());
		//this->objas[i]->draw(width, height, this->m_vst, this->m_pst, forward, right);
	}

	for (int i = 0; i < this->objbs.size(); i++)
	{
		//this->cubes[i]->setScale(Vector3D(scale, scale, scale));
		//this->cubes[i]->setRot(Vector3D(rotX, rotY, 0.0f));
		//this->objs[i]->setAnimSpeed(1.0f);
		//this->objs[i]->update(EngineTime::getDeltaTime());
		//this->objbs[i]->draw(width, height, this->m_vst, this->m_pst, forward, right);
	}

	//for (int i = 0; i < this->planes.size(); i++)
	//{
	//	//this->planes[i]->setScale(Vector3D(scale * 3.0f, scale * 0.1, scale * 3.0f));
	//	//this->planes[i]->setPos(Vector3D(0.0f, 0.0f, 0.0f));
	//	//this->planes[i]->setRot(Vector3D(rotX, rotY, 2.0f));
	//	this->planes[i]->draw(width, height, this->m_vs, this->m_ps, forward, right);
	//}

	SceneCameraHandler::get()->update();

	UIManager::get()->drawUI();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//m_vb->release();
	//SceneCameraHandler::destroy();
	m_swap_chain->release();
	//m_vs->release();
	//m_ps->release();
	GraphicsEngine::get()->release();
	MeshManager::get()->destroy;
	TextureManager::get()->destroy();
	
	
	UIManager::get()->destroy();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	/*if (key == 'W')
	{
		//rotX += 0.707f * EngineTime::getDeltaTime();
		forward = 1.0f;
	}
	else if (key == 'S')
	{
		forward = -1.0f;
	}
	else if (key == 'D')
	{
		right = 1.0f;
	}
	else if (key == 'A')
	{
		right = -1.0f;
	}*/
}

void AppWindow::onKeyUp(int key)
{
	//forward = 0.0f;
	//right = 0.0f;
}

void AppWindow::onMouseMove(const Point& mousePos)
{
	/*int width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	int height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	rotX += (mousePos.y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	rotY += (mousePos.x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	InputSystem::get()->setCursorPos(Point(width / 2.0f, height / 2.0f));*/
}

void AppWindow::onLMD(const Point& mousePos)
{
	//scale = 0.5f;
}

void AppWindow::onLMU(const Point& mousePos)
{
	//scale = 1.0f;
}

void AppWindow::onRMD(const Point& mousePos)
{
	//scale = 2.5f;
}

void AppWindow::onRMU(const Point& mousePos)
{
	//scale = 1.0f;
}
