#include "index_buffer.h"
#include "gl_error_handling.h"

IndexBuffer::IndexBuffer(const unsigned* data, unsigned count) {
    GLCALL(glGenBuffers(1, &m_index_buffer_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_index_buffer_id))
}

void IndexBuffer::bind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id));
}

void IndexBuffer::unbind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}