#include "vertex_array.h"
#include "gl_error_handling.h"

VertexArray::VertexArray() {
	GLCALL(glGenVertexArrays(1, &m_vertex_array_id));
}

VertexArray::~VertexArray() {
	GLCALL(glDeleteVertexArrays(1, &m_vertex_array_id));
}

void VertexArray::bind() const {
	GLCALL(glBindVertexArray(m_vertex_array_id));
}

void VertexArray::unbind() const {
	GLCALL(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout) {
	bind();
	vb->bind();
	unsigned offset = 0;
	const auto& attribs = layout->getAttribs();
	for (unsigned i = 0; i < attribs.size(); i++) {
		const VertexAttrib& attrib = attribs[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized, layout->getStride(), (const void*)offset));
		offset += attrib.count * attrib.type_size;
	}
}