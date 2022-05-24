#include "window.h"

#include <iostream>

#include <GL/glew.h>

Window::Window(unsigned width, unsigned height, std::string name)
	: m_width(width), m_height(height), m_name(name), m_window(nullptr) {
	
	// first window created
	if (m_all_windows.empty()) {
		// initialize glfw
		if (!glfwInit()) {
			std::cout << "Failed to initialize GLFW" << std::endl;
			m_current_window = nullptr;
			std::cout << "Could not create window" << std::endl;
			glfwTerminate();
		}
		else {
			m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
			m_current_window = m_window;
			m_all_windows.push_back(m_window);
			
			glfwMakeContextCurrent(m_window);
			glfwSetWindowCloseCallback(m_window, windowCloseCallback);
			
			// initialize GLEW
			if (glewInit() != GLEW_OK) {
				std::cout << "Error in glewInit" << std::endl;
			}
			std::cout << glGetString(GL_VERSION) << std::endl;
		}

	}
	else {
		m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		if (!m_window) {
			std::cout << "Could not create window" << std::endl;
		}
		else {
			m_all_windows.push_back(m_window);
		}
	}
}

Window::~Window() {
	windowCloseCallback(m_window);
	if (m_all_windows.empty()) {
		glfwTerminate();
	}
}

void Window::makeCurrent() {
	m_current_window = m_window;
	glfwMakeContextCurrent(m_window);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error in glewInit" << std::endl;
	}
}

int Window::windowShouldClose() {
	return glfwWindowShouldClose(m_window);
}

void Window::windowCloseCallback(GLFWwindow* window) {
	for (auto it = m_all_windows.begin(); it != m_all_windows.end(); it++) {
		if (*it == window) {
			m_all_windows.erase(it);
		}
	}
}