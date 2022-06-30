#pragma once

#include "Geometry.h"
#include "VertexArray.h"
#include "Texture.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Mesh {
public:
	Mesh(
		const Geometry& geometry,
		const std::vector<Texture*>& textures
	);
	~Mesh();

	void bind() const;
	void updateMatrix();
	void setGeometry(const Geometry& geometry);

	inline unsigned getNumTextures() const { return m_textures.size(); }
	inline unsigned getNumVertices() const { return m_num_vertices; }
	inline unsigned getNumIndices() const { return m_num_indices; }

	inline glm::vec3 getPosition() const { return m_position; }
	inline glm::vec3 getScale() const { return m_scale; }
	inline glm::quat getQuaternion() const { return m_quaternion; }

	inline void setMatrix(const glm::mat4& matrix) { m_matrix = matrix; }
	inline void setNormalMatrix(const glm::mat4& matrix) { m_normalMatrix = matrix; }
	inline void setMatrixAutoUpdate(bool flag) { m_matrixAutoUpdate = flag; }

private:
	std::vector<Texture*> m_textures;
	VertexArray* m_va;

	unsigned m_num_vertices;
	unsigned m_num_indices;

	glm::mat4 m_matrix; // model transformation
	glm::mat4 m_normalMatrix; // normal vector transformation
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::quat m_quaternion;
	bool m_matrixAutoUpdate;
};