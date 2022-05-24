#pragma once

#include <vector>
#include <GL/glew.h>

#include "vertex_buffer.h"

struct VertexAttrib {
	unsigned type;
	unsigned count;
	unsigned type_size;
	unsigned char normalized;
};

class VertexBufferLayout {
private:
	std::vector<VertexAttrib> m_attribs;
	unsigned m_stride;
public:
	VertexBufferLayout() : m_stride(0) {}

	template<typename T>
	void push(unsigned count) { static_assert(false); }

	template<>
	void push<float>(unsigned count) {
		m_attribs.push_back({ GL_FLOAT, count, sizeof(float), GL_FALSE });
		m_stride += count * sizeof(float);
	}

	template<>
	void push<unsigned>(unsigned count) {
		m_attribs.push_back({ GL_UNSIGNED_INT, count, sizeof(unsigned), GL_FALSE });
		m_stride += count * sizeof(unsigned);
	}

	template<>
	void push<unsigned char>(unsigned count) {
		m_attribs.push_back({ GL_UNSIGNED_BYTE, count, sizeof(unsigned char), GL_TRUE });
		m_stride += count * sizeof(unsigned char);
	}

	inline const std::vector<VertexAttrib> getAttribs() const& { return m_attribs; }
	inline unsigned getStride() const { return m_stride; }
};

class VertexArray {
private:
	unsigned m_vertex_array_id;
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;
	void addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout);
};