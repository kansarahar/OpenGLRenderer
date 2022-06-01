#pragma once

#include "VertexArray.h"
#include "Shader.h"

class Renderer {
public:
	Renderer();

	void clear() const;
	void draw(const VertexArray* va, const Shader* shader) const;
};