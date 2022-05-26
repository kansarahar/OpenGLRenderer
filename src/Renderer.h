#pragma once

#include "VertexArray.h"
#include "Shader.h"

class Renderer {
public:
	Renderer();

	void clear(unsigned buffer_bits) const;
	void draw(const VertexArray* va, const Shader* shader) const;
};