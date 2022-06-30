#include "Mesh.h"
#include "Geometry.h"

#include <algorithm>

Mesh::Mesh(
	const Geometry& geometry,
	const std::vector<Texture*>& textures
)
	: m_textures(textures),
	m_matrix(glm::mat4(1.0f)),
	m_position(glm::vec3(0.0f)),
	m_scale(glm::vec3(1.0f)),
	m_quaternion(glm::quat()),
	m_matrixAutoUpdate(true)

{
	m_va = new VertexArray();
	m_va->addAttrib("position", GL_FLOAT, 3, false);
	m_va->addAttrib("normal", GL_FLOAT, 3, true);
	m_va->addAttrib("color", GL_FLOAT, 3, false);
	m_va->addAttrib("tex_coord", GL_FLOAT, 2, false);
	m_va->bindAttribLayout();

	setGeometry(geometry);
}

Mesh::~Mesh() {
	delete m_va;
}

void Mesh::bind() const {
	m_va->bind();
	unsigned slot = 0;
	for (Texture* texture : m_textures) {
		texture->bind(slot++);
	}
}

void Mesh::setGeometry(const Geometry& geometry) {
	m_va->bind();
	geometry.bindBuffers();
	m_num_vertices = geometry.getNumVertices();
	m_num_indices = geometry.getNumIndices();
}

void Mesh::updateMatrix() {
	// TODO
}
