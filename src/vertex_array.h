#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"

#include <vector>

#include <GL/glew.h>


struct VertexAttrib {
	GLenum type;
	unsigned size;
	unsigned type_byte_size;
	bool normalized;
};

class VertexArray {
private:
	unsigned m_vertex_array_id;
	unsigned m_stride;
	std::vector<VertexAttrib> m_attribs;
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;
	void addAttrib(GLenum type, unsigned size, bool normalized = false);
	void bindBuffers(const VertexBuffer* vb, const IndexBuffer* ib);
};
