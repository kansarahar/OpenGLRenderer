#pragma once

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include <vector>

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 tex_coord;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices);
	~Mesh();
	void bind() const;

private:
	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
};