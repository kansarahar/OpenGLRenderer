#include "VertexArray.h"
#include "GLErrorHandling.h"

#include <algorithm>
#include <iostream>

VertexArray::VertexArray()
	: m_vertex_array_id(0), m_stride(0)
{
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

void VertexArray::addAttrib(const std::string& attrib_name, GLenum type, unsigned size, bool normalized) {
	unsigned type_byte_size = 0;
	switch (type) {
	case GL_FLOAT:
		type_byte_size = sizeof(GLfloat);
		break;
	case GL_DOUBLE:
		type_byte_size = sizeof(GLdouble);
		break;
	case GL_INT:
		type_byte_size = sizeof(GLint);
		break;
	case GL_UNSIGNED_INT:
		type_byte_size = sizeof(GLuint);
		break;
	case GL_BYTE:
		type_byte_size = sizeof(GLbyte);
		break;
	case GL_UNSIGNED_BYTE:
		type_byte_size = sizeof(GLubyte);
		break;
	case GL_SHORT:
		type_byte_size = sizeof(GLshort);
		break;
	case GL_UNSIGNED_SHORT:
		type_byte_size = sizeof(GLushort);
		break;
	case GL_FIXED:
		type_byte_size = sizeof(GLfixed);
		break;
	case GL_HALF_FLOAT:
		type_byte_size = sizeof(GLhalf);
		break;
	default:
		std::cout << "Error in VertexArray::addAttrib: Not a valid GLenum type - using GL_FLOAT as default" << std::endl;
		type_byte_size = sizeof(GLfloat);
	}
	m_attribs.push_back({ type, size, type_byte_size, normalized });
	m_stride += size * type_byte_size;
}

void VertexArray::bindAttribLayout() {
	bind();
	unsigned offset = 0;
	for (unsigned i = 0; i < m_attribs.size(); i++) {
		const VertexAttrib& attrib = m_attribs[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, attrib.size, attrib.type, attrib.normalized ? GL_TRUE : GL_FALSE, m_stride, (const void*)offset));
		offset += attrib.size * attrib.type_byte_size;
	}
}

