#include "Geometry.h"

#include <vector>

Geometry::Geometry(const std::vector<Vertex> vertices, const std::vector<unsigned> indices)
	: m_vertices(vertices), m_indices(indices),
	  m_num_vertices(vertices.size()), m_num_indices(indices.size()),
	  m_vb(nullptr), m_ib(nullptr)
{
	m_vb = new VertexBuffer(&vertices[0], static_cast<unsigned>(vertices.size() * sizeof(Vertex)));
	m_ib = new IndexBuffer(&indices[0], static_cast<unsigned>(indices.size() * sizeof(unsigned)));
}

Geometry::~Geometry() {
	delete m_vb;
	delete m_ib;
}

void Geometry::bindBuffers() const {
	m_vb->bind();
	m_ib->bind();
}