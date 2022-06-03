#include "Window.h"

#include <iostream>
#include <assert.h>

Window::Window(int width, int height, std::string name, Camera* cam) :
	m_width(width), m_height(height), m_name(name), m_cam(cam), m_window(nullptr),
	delta_time(0.0f), time_curr_frame(0.0f), time_prev_frame(0.0f),
	first_mouse(true), prev_mouse_x(0.0), prev_mouse_y(0.0)
{

	/* This is the first window created */
	assert(!created_window);

	if (!glfwInit()) {

		/* GLFW failed to initialize */
		std::cout << "Failed to initialize GLFW" << std::endl;
		std::cout << "Could not create window" << std::endl;
		glfwTerminate();
	}
	else {

		/* GLFW initialized successfully */
		m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		created_window = this;

		glfwMakeContextCurrent(m_window);

		/* Initialize GLEW */
		if (glewInit() != GLEW_OK) {
			std::cout << "Error in glewInit" << std::endl;
		}
		std::cout << glGetString(GL_VERSION) << std::endl;

		setCallbackFunctions(m_window);
	}
}

Window::~Window() {
	windowCloseCallback(m_window);
	glfwTerminate();
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
	if (created_window->first_mouse) {
		created_window->prev_mouse_x = xpos;
		created_window->prev_mouse_y = ypos;
		created_window->first_mouse = false;
	}
	float xoffset = xpos - created_window->prev_mouse_x;
	float yoffset = created_window->prev_mouse_y - ypos;

	created_window->prev_mouse_x = xpos;
	created_window->prev_mouse_y = ypos;
	created_window->m_cam->rotate(xoffset, yoffset);
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	created_window->m_cam->changeFov(-yoffset);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &(created_window->m_width), &(created_window->m_height));
}

void Window::windowCloseCallback(GLFWwindow* window) {
	setCallbackFunctions(window, true);
	created_window = nullptr;
}

void Window::setCallbackFunctions(GLFWwindow* window, bool unset) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, unset ? NULL : mouseCallback);
	glfwSetScrollCallback(window, unset ? NULL : scrollCallback);
	glfwSetFramebufferSizeCallback(window, unset ? NULL : framebufferSizeCallback);
	glfwSetWindowCloseCallback(window, unset ? NULL : windowCloseCallback);
}

Window* Window::created_window = nullptr;