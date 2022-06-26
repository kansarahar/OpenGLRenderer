#pragma once

#include "Mesh.h"
#include "Shader.h"

class Renderer {
public:
	Renderer();

	void clear() const;
	void draw(const Mesh* mesh, const Shader* shader) const;
};