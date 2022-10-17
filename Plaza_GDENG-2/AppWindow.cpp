#include "AppWindow.h"
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
}

void AppWindow::onCreate()
{
	Window::onCreate();
	EngineTime::initialize();
	GraphicsEngine::get()->init();
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
	

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	//m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		float x = float(rand()) / float(RAND_MAX) * (0.75f - -0.75f) + -0.75f;
		float y = float(rand()) / float(RAND_MAX) * (0.75f - -0.75f) + -0.75f;

		Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);
		cubeObject->setAnimSpeed(float(rand()) / float(RAND_MAX) * (3.75f - -3.75f) + -3.75f);
		cubeObject->setPos(Vector3D(x, y, 0.0f));
		cubeObject->setScale(Vector3D(0.25, 0.25, 0.25));
		this->cubes.push_back(cubeObject);
	}

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	//constant cc;

	//cc.m_time = 0;

	//m_cb = GraphicsEngine::get()->createConstantBuffer();
	//m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	this->ticks += EngineTime::getDeltaTime();
	Window::onUpdate();
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
		this->cubes[i]->update(EngineTime::getDeltaTime());
		this->cubes[i]->draw(width, height, this->m_vs, this->m_ps);
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//m_vb->release();
	m_swap_chain->release();
	//m_vs->release();
	//m_ps->release();
	GraphicsEngine::get()->release();
}