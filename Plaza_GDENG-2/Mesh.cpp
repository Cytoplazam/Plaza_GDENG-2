#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>

#include "GraphicsEngine.h" 
#include "VertexMesh.h"

Mesh::Mesh(const wchar_t* full_path): Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> mats;

	std::string warn;
	std::string err;

	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &full_path[0], wcslen(full_path), NULL, 0, NULL, NULL);
	std::string inputfile(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &full_path[0], -1, &inputfile[0], size_needed, NULL, NULL);

	bool res = tinyobj::LoadObj(&attribs, &shapes, &mats, &warn, &err, inputfile.c_str());

	if (!err.empty())
		throw std::exception("Mesh not created successfully");

	if (!res)
		throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1)
		throw std::exception("Mesh not created successfully");

	std::vector<VertexMesh> list_verts;
	std::vector<unsigned int> list_indices;

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_verts.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_verts.push_back(vertex);

				list_indices.push_back((unsigned int)index_offset + v);
			}
		
			index_offset += num_face_verts;
		}
	}
	
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);

	this->m_vertex_buffer = GraphicsEngine::get()->createVertexBufferTex();
	this->m_vertex_buffer->load(&list_verts[0], sizeof(VertexMesh), (UINT)list_verts.size(), shader_byte_code, (UINT)size_shader);

	this->m_index_buffer = GraphicsEngine::get()->createIndexBuffer();
	this->m_index_buffer->load(&list_indices[0], (UINT)list_indices.size());
}

Mesh::~Mesh()
{
}

VertexBufferTex* Mesh::getVertexBuffer()
{
	return m_vertex_buffer;
}

IndexBuffer* Mesh::getIndexBuffer()
{
	return m_index_buffer;
}
