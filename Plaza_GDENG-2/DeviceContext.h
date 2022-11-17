#pragma once
#include <d3d11.h>
#include "Texture.h"

class SwapChain;
class VertexBuffer;
class VertexBufferTex;
class VertexShader;
class IndexBuffer;
class PixelShader;
class ConstantBuffer;
class Texture;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);

	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);

	void setVertexBuffer(VertexBuffer* vertex_buffer);

	void setVertexBufferTex(VertexBufferTex* vertex_buffer_tex);

	void setIndexBuffer(IndexBuffer* index_buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);

	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);

	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setTexture(VertexShader* vertex_shader, Texture* tex);
	void setTexture(PixelShader* pixel_shader, Texture* tex);

	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

	bool release();

	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
private:
	friend class ConstantBuffer;
};

