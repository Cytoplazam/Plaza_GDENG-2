#pragma once
#include "Resource.h"
#include "VertexBufferTex.h"
#include "IndexBuffer.h"

class Mesh: public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	VertexBufferTex* getVertexBuffer();
	IndexBuffer* getIndexBuffer();
private:
	VertexBufferTex* m_vertex_buffer;
	IndexBuffer* m_index_buffer;
private:
	friend class DeviceContext;
};

