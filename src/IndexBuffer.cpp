#include "IndexBuffer.h"
#include "GLErrorHandling.h"

#include <algorithm>

IndexBuffer::IndexBuffer(const unsigned* data, unsigned count)
    : m_count(count) 
{
    GLCALL(glGenBuffers(1, &m_index_buffer_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(const IndexBuffer& other) {
    *this = other;
}

IndexBuffer& IndexBuffer::operator=(const IndexBuffer& other) {

    // copy
    unsigned new_index_buffer_id;
    GLCALL(glGenBuffers(1, &new_index_buffer_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, new_index_buffer_id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, other.m_count * sizeof(unsigned), nullptr, GL_STATIC_DRAW));

    GLCALL(glBindBuffer(GL_COPY_READ_BUFFER, other.m_index_buffer_id));
    GLCALL(glBindBuffer(GL_COPY_WRITE_BUFFER, new_index_buffer_id));
    GLCALL(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, other.m_count * sizeof(unsigned)));

    // swap and delete
    std::swap(m_index_buffer_id, new_index_buffer_id);
    m_count = other.m_count;

    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id));
    GLCALL(glDeleteBuffers(1, &new_index_buffer_id));

    return *this;
}

IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_index_buffer_id));
}

void IndexBuffer::bind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id));
}

void IndexBuffer::unbind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}