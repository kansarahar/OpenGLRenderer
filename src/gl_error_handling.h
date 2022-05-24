#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();     // MSVC intrinsic debug break
#define GLCALL(x) clearError(); x; ASSERT(checkError(#x, __FILE__, __LINE__));

void clearError();
bool checkError(const char* function, const char* file, int line);