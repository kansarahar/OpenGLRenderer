#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <vector>

#include "glm/glm.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 tex_coord;
};

class Geometry {
public:
	Geometry(const std::vector<Vertex> vertices, const std::vector<unsigned> indices);
	~Geometry();

	void bindBuffers() const;

	inline std::vector<Vertex> getVertices() const { return m_vertices; }
	inline std::vector<unsigned> getIndices() const { return m_indices; }
	inline unsigned getNumVertices() const { return m_num_vertices; }
	inline unsigned getNumIndices() const { return m_num_indices; }

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned> m_indices;
	unsigned m_num_vertices;
	unsigned m_num_indices;

	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
};