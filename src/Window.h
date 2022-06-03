#pragma once

#include "Camera.h"

#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* Singleton window class */
class Window {
public:
	Window(int width, int height, std::string name, Camera* cam);
	Window(Window& window) = delete;
	~Window();
	
	void bind();
	void processInput();
	
	inline void swapBuffers() { glfwSwapBuffers(m_window); }
	inline void pollEvents() { glfwPollEvents(); }
	inline bool isClosed() { return !created_window || glfwWindowShouldClose(m_window); }
	
private:
	/* Static functions and members */
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void windowCloseCallback(GLFWwindow* window);
	static void setCallbackFunctions(GLFWwindow* window, bool unset=false);
	static Window* created_window;

	/* Values useful for callback calculations */
	float delta_time, time_curr_frame, time_prev_frame;
	bool first_mouse;
	double prev_mouse_x, prev_mouse_y;

	/* Non-static members */
	GLFWwindow* m_window;
	Camera* m_cam;
	std::string m_name;
	int m_width, m_height;
};