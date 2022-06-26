#include "Renderer.h"
#include "GLErrorHandling.h"
#include "Mesh.h"

#include <GL/glew.h>

Renderer::Renderer() {
	GLCALL(glEnable(GL_DEPTH_TEST));
	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::clear() const {
	GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(const Mesh* mesh, const Shader* shader) const {
	shader->bind();
	mesh->bind();
	GLCALL(glDrawElements(GL_TRIANGLES, mesh->getNumIndices(), GL_UNSIGNED_INT, nullptr));
}