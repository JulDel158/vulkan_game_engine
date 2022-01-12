#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace ve {

class ve_window {
public:
	ve_window(int w, int h, std::string name);
	~ve_window();

	bool shouldClose() {
		return glfwWindowShouldClose(window);
	};

private:
	void initWindow();

	const int width;
	const int height;

	std::string windowName;
	GLFWwindow* window;
};

} // namespace ve