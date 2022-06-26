#include "Mesh.h"

#include <algorithm>

Mesh::Mesh(
	const std::vector<Vertex>& vertices,
	const std::vector<unsigned>& indices,
	const std::vector<Texture*>& textures
)
	: m_vertices(vertices), m_indices(indices), m_textures(textures)
{
	m_vb = new VertexBuffer(&vertices[0], static_cast<unsigned>(vertices.size() * sizeof(Vertex)));
	m_ib = new IndexBuffer(&indices[0], static_cast<unsigned>(indices.size() * sizeof(unsigned)));
	m_va = new VertexArray();

	m_va->addAttrib("position", GL_FLOAT, 3, false);
	m_va->addAttrib("normal", GL_FLOAT, 3, true);
	m_va->addAttrib("color", GL_FLOAT, 3, false);
	m_va->addAttrib("tex_coord", GL_FLOAT, 2, false);
	m_va->bindBuffers(m_vb, m_ib);
}

Mesh::~Mesh() {
	delete m_vb;
	delete m_ib;
	delete m_va;
}

void Mesh::bind() const {
	m_va->bind();
	unsigned slot = 0;
	for (Texture* texture : m_textures) {
		texture->bind(slot++);
	}
}