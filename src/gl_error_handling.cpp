#include "gl_error_handling.h"

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