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

VertexBuffer::VertexBuffer(const VertexBuffer& other) {
    *this = other;
}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other) {

    // copy
    unsigned new_vertex_buffer_id;
    GLCALL(glGenBuffers(1, &new_vertex_buffer_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, new_vertex_buffer_id));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, other.m_size, nullptr, GL_STATIC_DRAW));

    GLCALL(glBindBuffer(GL_COPY_READ_BUFFER, other.m_vertex_buffer_id));
    GLCALL(glBindBuffer(GL_COPY_WRITE_BUFFER, new_vertex_buffer_id));
    GLCALL(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, other.m_size));

    // swap and delete
    std::swap(m_vertex_buffer_id, new_vertex_buffer_id);
    m_size = other.m_size;

    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id));
    GLCALL(glDeleteBuffers(1, &new_vertex_buffer_id));

    return *this;
}

void VertexBuffer::bind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id));
}

void VertexBuffer::unbind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
