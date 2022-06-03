#include "Window.h"

#include <iostream>

Window::Window(int width, int height, std::string name, Camera* cam, Window* window_to_share_context) :
	m_width(width), m_height(height), m_name(name), m_cam(cam), m_window(nullptr),
	delta_time(0.0f), time_curr_frame(0.0f), time_prev_frame(0.0f),
	first_mouse(true), prev_mouse_x(0.0), prev_mouse_y(0.0),
	window_destroyed(false)
{

	/* This is the first window created */
	if (m_all_windows.empty()) {
		if (!glfwInit()) {

			/* GLFW failed to initialize */
			std::cout << "Failed to initialize GLFW" << std::endl;
			std::cout << "Could not create window" << std::endl;
			glfwTerminate();

		}
		else {

			/* GLFW initialized successfully */
			m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
			m_all_windows[m_window] = this;

			glfwMakeContextCurrent(m_window);

			/* Initialize GLEW */
			if (glewInit() != GLEW_OK) {
				std::cout << "Error in glewInit" << std::endl;
			}
			std::cout << glGetString(GL_VERSION) << std::endl;

			setCallbackFunctions(m_window);
		}
	}
	else {
		m_window = glfwCreateWindow(width, height, name.c_str(), NULL, window_to_share_context ? window_to_share_context->m_window : NULL);
		if (!m_window)
			std::cout << "Could not create window" << std::endl;
		else {
			m_all_windows[m_window] = this;
			setCallbackFunctions(m_window);
		}
	}
}

Window::~Window() {
	windowCloseCallback(m_window);
	if (m_all_windows.empty()) {
		glfwTerminate();
		std::cout << "terminated" << std::endl;
	}
}

void Window::bind() {
	glfwMakeContextCurrent(m_window);
	if (glewInit() != GLEW_OK)
		std::cout << "Error in glewInit" << std::endl;
}

void Window::processInput() {
	time_curr_frame = (float)glfwGetTime();
	delta_time = time_curr_frame - time_prev_frame;
	time_prev_frame = time_curr_frame;

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_cam->moveForward(delta_time);
	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_cam->moveBackward(delta_time);
	if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_cam->moveLeft(delta_time);
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_cam->moveRight(delta_time);
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_cam->moveUp(delta_time);
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		m_cam->moveDown(delta_time);
}

void Window::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	Window* curr_window = m_all_windows[window];
	if (curr_window->first_mouse) {
		curr_window->prev_mouse_x = xpos;
		curr_window->prev_mouse_y = ypos;
		curr_window->first_mouse = false;
	}
	float xoffset = xpos - curr_window->prev_mouse_x;
	float yoffset = curr_window->prev_mouse_y - ypos;

	curr_window->prev_mouse_x = xpos;
	curr_window->prev_mouse_y = ypos;
	curr_window->m_cam->rotate(xoffset, yoffset);
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	Window* curr_window = m_all_windows[window];
	curr_window->m_cam->changeFov(-yoffset);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	Window* curr_window = m_all_windows[window];
	glfwGetWindowSize(window, &(curr_window->m_width), &(curr_window->m_height));
}

void Window::windowCloseCallback(GLFWwindow* window) {
	/* Remove window from list of existing windows */
	auto window_it = m_all_windows.find(window);
	if (window_it != m_all_windows.end()) {
		m_all_windows[window]->window_destroyed = true;
		m_all_windows.erase(window_it);
		glfwDestroyWindow(window);
	}
}

void Window::setCallbackFunctions(GLFWwindow* window) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glfwSetWindowCloseCallback(window, windowCloseCallback);
}

std::unordered_map<GLFWwindow*, Window*> Window::m_all_windows;