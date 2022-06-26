#pragma once

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"

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
	Mesh(
		const std::vector<Vertex>& vertices,
		const std::vector<unsigned>& indices,
		const std::vector<Texture*>& textures
	);
	~Mesh();

	void bind() const;

	inline unsigned getNumVertices() const { return m_vertices.size();}
	inline unsigned getNumIndices() const { return m_indices.size(); }
	inline unsigned getNumTextures() const { return m_textures.size(); }

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned> m_indices;
	std::vector<Texture*> m_textures;

	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexArray* m_va;
};