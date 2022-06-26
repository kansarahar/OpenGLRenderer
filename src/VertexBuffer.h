#pragma once

class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned size);
	VertexBuffer(const VertexBuffer& other);
	VertexBuffer& operator=(const VertexBuffer& other);
	~VertexBuffer();


	void bind() const;
	void unbind() const;

private:
	unsigned m_vertex_buffer_id;
	unsigned m_size;
};