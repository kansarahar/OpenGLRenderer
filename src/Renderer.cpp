#include "Renderer.h"
#include "GLErrorHandling.h"

#include <GL/glew.h>

Renderer::Renderer() {
	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::clear(unsigned buffer_bits) const {
	GLCALL(glClear(buffer_bits))
}

void Renderer::draw(const VertexArray* va, const Shader* shader) const {
	shader->bind();
	va->bind();
	GLCALL(glDrawElements(GL_TRIANGLES, va->getElementCount(), GL_UNSIGNED_INT, nullptr));
}