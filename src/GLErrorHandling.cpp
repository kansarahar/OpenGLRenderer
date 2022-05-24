#include "GLErrorHandling.h"

#include <iostream>

void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool checkError(const char* function, const char* file, int line) {
	while (unsigned error = glGetError()) {
		std::cout << "[OpenGL error] (" << error << "): "
			<< function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

unsigned checkShaderCompilationError(GLenum type, unsigned shader_program_id) {
    int compilation_result;
    glGetShaderiv(shader_program_id, GL_COMPILE_STATUS, &compilation_result);
    if (compilation_result == GL_FALSE) {
        int length;
        glGetShaderiv(shader_program_id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(shader_program_id, length, &length, message);
        std::cout << "[OpenGL error] (Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader):\n";
        std::cout << message << std::endl;
        delete[] message;
        return GL_FALSE;
    }
    return shader_program_id;
}