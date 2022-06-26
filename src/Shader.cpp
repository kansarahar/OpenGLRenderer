#include "Shader.h"
#include "GLErrorHandling.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
	: m_shader_program_id(0)
{
	m_shader_program_id = glCreateProgram();

	std::string vertex_shader_source = parseShader(vertex_shader_filepath);
	std::string fragment_shader_source = parseShader(fragment_shader_filepath);

	unsigned vs_id = compileShader(GL_VERTEX_SHADER, vertex_shader_source);
	unsigned fs_id = compileShader(GL_FRAGMENT_SHADER, fragment_shader_source);

	GLCALL(glAttachShader(m_shader_program_id, vs_id));
	GLCALL(glAttachShader(m_shader_program_id, fs_id));

	GLCALL(glLinkProgram(m_shader_program_id));
	GLCALL(glValidateProgram(m_shader_program_id));

	GLCALL(glDeleteShader(vs_id));
	GLCALL(glDeleteShader(fs_id));
}

Shader::~Shader() {
	GLCALL(glDeleteProgram(m_shader_program_id));
}

void Shader::bind() const {
	GLCALL(glUseProgram(m_shader_program_id));
}

void Shader::unbind() const {
	GLCALL(glUseProgram(0));
}

std::string Shader::parseShader(const std::string& filepath) {
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss;
	while (getline(stream, line)) {
		ss << line << '\n';
	}
	return ss.str();
}

unsigned Shader::compileShader(GLenum type, const std::string& source) {
	unsigned shader_id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader_id, 1, &src, nullptr);
	glCompileShader(shader_id);

	unsigned compilation_result = checkShaderCompilationError(type, shader_id);
	if (compilation_result == GL_FALSE) {
		glDeleteShader(shader_id);
		return GL_FALSE;
	}

	return shader_id;
}

int Shader::getUniformLocation(const std::string& name) {
	if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
		return m_uniform_location_cache[name];

	GLCALL(int location = glGetUniformLocation(m_shader_program_id, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' does not exist." << std::endl;

	m_uniform_location_cache[name] = location;
	return location;
}

void Shader::setUniform1i(const std::string& name, int v0) {
	GLCALL(glUniform1i(getUniformLocation(name), v0));
}

void Shader::setUniform2i(const std::string& name, int v0, int v1) {
	GLCALL(glUniform2i(getUniformLocation(name), v0, v1));
}

void Shader::setUniform3i(const std::string& name, int v0, int v1, int v2) {
	GLCALL(glUniform3i(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform4i(const std::string& name, int v0, int v1, int v2, int v3) {
	GLCALL(glUniform4i(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1f(const std::string& name, float v0) {
	GLCALL(glUniform1f(getUniformLocation(name), v0));
}

void Shader::setUniform2f(const std::string& name, float v0, float v1) {
	GLCALL(glUniform2f(getUniformLocation(name), v0, v1));
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) {
	GLCALL(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMatrix2f(const std::string& name, const glm::mat2& mat) {
	GLCALL(glUniformMatrix2fv(getUniformLocation(name), 1, false, glm::value_ptr(mat)));
}

void Shader::setUniformMatrix3f(const std::string& name, const glm::mat3& mat) {
	GLCALL(glUniformMatrix3fv(getUniformLocation(name), 1, false, glm::value_ptr(mat)));
}

void Shader::setUniformMatrix4f(const std::string& name, const glm::mat4& mat) {
	GLCALL(glUniformMatrix4fv(getUniformLocation(name), 1, false, glm::value_ptr(mat)));
}
