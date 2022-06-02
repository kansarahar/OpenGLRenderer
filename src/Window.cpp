#include "Window.h"

#include <iostream>

#include <GL/glew.h>


Window::Window(unsigned width, unsigned height, std::string name, Camera* cam, Window* window_to_share_context)
	: m_width(width), m_height(height), m_name(name), m_cam(cam), m_window(nullptr)
{
	if (m_all_window_ptrs.empty()) {
		// initialize glfw
		if (!glfwInit()) {
			std::cout << "Failed to initialize GLFW" << std::endl;
			std::cout << "Could not create window" << std::endl;
			glfwTerminate();
		}
		else {
			m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
			m_all_window_ptrs.push_back(m_window);

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
		m_window = glfwCreateWindow(width, height, name.c_str(), NULL, window_to_share_context->m_window);
		if (!m_window)
			std::cout << "Could not create window" << std::endl;
		else
			m_all_window_ptrs.push_back(m_window);
	}
}

Window::~Window() {
	windowCloseCallback(m_window);
	if (m_all_window_ptrs.empty())
		glfwTerminate();
}

void Window::bind() {
	glfwMakeContextCurrent(m_window);
	if (glewInit() != GLEW_OK)
		std::cout << "Error in glewInit" << std::endl;
}

void Window::windowCloseCallback(GLFWwindow* window) {
	for (auto it = m_all_window_ptrs.begin(); it != m_all_window_ptrs.end(); it++) {
		if (*it == window)
			m_all_window_ptrs.erase(it);
	}
}

std::vector<GLFWwindow*> Window::m_all_window_ptrs;