#pragma once

#include <vector>
#include <string>

#include <GLFW/glfw3.h>

class Window {
public:
	Window(unsigned width, unsigned height, std::string name);
	~Window();

	void makeCurrent();
	int windowShouldClose();

private:
	static std::vector<GLFWwindow*> m_all_windows;
	static GLFWwindow* m_current_window;
	
	GLFWwindow* m_window;
	unsigned m_width, m_height;
	std::string m_name;

	static void windowCloseCallback(GLFWwindow* window);
};

