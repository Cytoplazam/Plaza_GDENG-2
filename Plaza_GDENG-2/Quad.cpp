#include "Quad.h"

/*struct vec3
{
	float x, y, z;
};*/

struct vertex
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
	unsigned int m_time;
};

Quad::Quad()
{
	vertex list[] =
	{
		//RAINBOW TRIANGLE
		//{-0.5f, -0.5f, 0.0f, 1, 0, 0},
		//{0.0f, 0.5f, 0.0f, 0, 1, 0},
		//{0.5f, -0.5f, 0.0f, 0, 0, 1}

		//RAINBOW RECTANGLE
		//Triangle List 
		
		{Vector3D(-0.5f, -0.5f, 0.0f),  Vector3D(-0.32f, -0.11f, 0.0f),   Vector3D(0, 0, 0),   Vector3D(0, 1, 0)},
		{Vector3D(-0.5f, 0.5f, 0.0f),   Vector3D(-0.11f, 0.78f, 0.0f),    Vector3D(1, 1, 0),   Vector3D(0, 1, 1)},
		{Vector3D(0.5f, -0.5f, 0.0f),   Vector3D(0.75f, -0.73f, 0.0f),    Vector3D(0, 0, 1),   Vector3D(1, 0, 0)},
		{Vector3D(0.5f, 0.5f, 0.0f),    Vector3D(0.88f, 0.7f, 0.0f),      Vector3D(1, 1, 1),   Vector3D(0, 0, 1)}

		// Slide 13	
		/*
		{Vector3D(-0.7f, -0.9f, 0.0f),  Vector3D(-0.32f, -0.11f, 0.0f),   Vector3D(0, 0, 0),   Vector3D(0, 1, 0)},
		{Vector3D(-0.9f, 0.2f, 0.0f),   Vector3D(-0.11f, 0.78f, 0.0f),    Vector3D(1, 1, 0),   Vector3D(0, 1, 1)},
		{Vector3D(0.2f, -0.3f, 0.0f),   Vector3D(0.75f, -0.73f, 0.0f),    Vector3D(0, 0, 1),   Vector3D(1, 0, 0)},
		{Vector3D(0.1f, 0.2f, 0.0f),    Vector3D(0.88f, 0.7f, 0.0f),      Vector3D(1, 1, 1),   Vector3D(0, 0, 1)}*/

		// Slide 14
		/*
		{Vector3D(-0.6f, -0.8f, 0.0f),  Vector3D(-0.2f, -0.1f, 0.0f),   Vector3D(0, 0, 0),   Vector3D(0, 1, 0)},
		{Vector3D(-0.8f, 0.2f, 0.0f),   Vector3D(0.0f, 0.8f, 0.0f),    Vector3D(1, 1, 0),   Vector3D(0, 1, 1)},
		{Vector3D(0.9f, -0.2f, 0.0f),   Vector3D(0.1f, -0.7f, 0.0f),    Vector3D(0, 0, 1),   Vector3D(1, 0, 0)},
		{Vector3D(-0.6f, -0.8f, 0.0f),    Vector3D(0.8f, 0.8f, 0.0f),      Vector3D(1, 1, 1),   Vector3D(0, 0, 1)}*/

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
		{-0.5f, -0.5f, 0.0f}*/
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	//GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;

	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Quad::updateQuadPosition(float x, float y, float z, float width, float height, float sX, float sY)
{
	constant cc;

	if (time < 10 && time >= 0 && increasing)
	{
		time += EngineTime::getDeltaTime();
		ticks += time * 1.0f;
		cc.m_time = time * ticks;
	}
	else
	{
		increasing = false;
		time -= EngineTime::getDeltaTime();
		ticks -= time * 1.0f;
		cc.m_time = time * ticks;
		if (time <= 0)
		{
			increasing = true;
			time += EngineTime::getDeltaTime();
			ticks += time * 1.0f;
		}
	}

	//std::cout << time << "\n";

	m_delta_pos += (m_delta_time / 10.0f);

	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	Matrix4x4 temp;

	m_delta_scale += m_delta_time / 0.15f;

	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0.0), Vector3D(2, 2, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	//temp.setTranslation(Vector3D::lerp(Vector3D(x, y, z), Vector3D(1.5f, 1.5f, 0.0f), m_delta_pos));
	temp.setTranslation(Vector3D(x, y, x));
	cc.m_world.setScale(Vector3D(sX, sY, 0.5));
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_projection.setOrthoLH(width, height, -4.0f, 4.0f);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Quad::draw(float x, float y, float z, float width, float height, float sX, float sY)
{
	updateQuadPosition(x, y, z, width, height, sX, sY);
	/*Matrix4x4 temp;
	constant cc;
	cc.m_time = ::GetTickCount();

	temp.setTranslation(Vector3D(x, y, z));
	cc.m_world.setScale(Vector3D(0.5, 0.5, 0.0));
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_projection.setOrthoLH(width, height, -4.0f, 4.0f);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);*/

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	//m_old_delta = m_new_delta;
	//m_new_delta = ::GetTickCount();
	//m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

Quad::~Quad()
{
	m_vb->release();
	m_vs->release();
	m_ps->release();
}