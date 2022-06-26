#include "VertexBuffer.h"
#include "GLErrorHandling.h"

#include <algorithm>

VertexBuffer::VertexBuffer(const void* data, unsigned size)
    : m_size(size)
{
    GLCALL(glGenBuffers(1, &m_vertex_buffer_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_vertex_buffer_id))
}

void VertexBuffer::bind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id));
}

void VertexBuffer::unbind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
