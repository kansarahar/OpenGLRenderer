#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

class Shader {
public:
	Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
	Shader(const Shader& other) = delete;
	Shader& operator=(const Shader& other) = delete;
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform1i(const std::string& name, int v0);
	void setUniform2i(const std::string& name, int v0, int v1);
	void setUniform3i(const std::string& name, int v0, int v1, int v2);
	void setUniform4i(const std::string& name, int v0, int v1, int v2, int v3);
	void setUniform1f(const std::string& name, float v0);
	void setUniform2f(const std::string& name, float v0, float v1);
	void setUniform3f(const std::string& name, float v0, float v1, float v2);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniformMatrix2f(const std::string& name, const glm::mat2& mat);
	void setUniformMatrix3f(const std::string& name, const glm::mat3& mat);
	void setUniformMatrix4f(const std::string& name, const glm::mat4& mat);

private:
	std::string parseShader(const std::string& filepath);
	unsigned compileShader(GLenum type, const std::string& source);

	int getUniformLocation(const std::string& name);

	unsigned m_shader_program_id;
	std::unordered_map<std::string, int> m_uniform_location_cache;
};
