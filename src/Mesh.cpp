#include "Mesh.h"
#include "Texture.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices)
	: vertices(vertices), indices(indices)
{
	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));	
	ib = new IndexBuffer(&indices[0], indices.size() * sizeof(unsigned));
	va = new VertexArray();


	va->addAttrib("position", GL_FLOAT, 3, false);
	va->addAttrib("normal", GL_FLOAT, 3, true);
	va->addAttrib("color", GL_FLOAT, 3, false);
	va->addAttrib("tex_coord", GL_FLOAT, 2, false);
	va->bindBuffers(vb, ib);
}

Mesh::~Mesh() {
	delete vb;
	delete ib;
	delete va;
}

void Mesh::bind() const {
	va->bind();
}