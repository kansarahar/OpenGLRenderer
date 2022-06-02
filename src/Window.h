#pragma once

#include "Camera.h"

#include <string>
#include <vector>

#include <GLFW/glfw3.h>

/* Singleton window class */
class Window {
public:
	Window(unsigned width, unsigned height, std::string name, Camera* cam, Window* window_to_share_context=NULL);
	Window(Window& window) = delete;
	~Window();
	
	void bind();
	void processInput();
	
	inline void swapBuffers() { glfwSwapBuffers(m_window); }
	inline void pollEvents() { glfwPollEvents(); }
	inline int windowShouldClose() { return glfwWindowShouldClose(m_window); }
	
private:
	static void windowCloseCallback(GLFWwindow* window);
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static std::vector<GLFWwindow*> m_all_window_ptrs;

	GLFWwindow* m_window;
	Camera* m_cam;
	std::string m_name;
	unsigned m_width, m_height;
};