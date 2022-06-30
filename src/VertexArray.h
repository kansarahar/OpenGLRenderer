#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <vector>
#include <string>

#include <GL/glew.h>


class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;
	void addAttrib(const std::string& attrib_name, GLenum type, unsigned size, bool normalized = false);
	void bindAttribLayout();

private:
	struct VertexAttrib {
		GLenum type;
		unsigned size;
		unsigned type_byte_size;
		bool normalized;
		std::string attrib_name;
	};

	unsigned m_vertex_array_id;
	unsigned m_stride;
	std::vector<VertexAttrib> m_attribs;
};
