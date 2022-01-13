#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace ve {

	// ve_window handles pointer to GLFWwindow class
class ve_window {
public:
	ve_window(int w, int h, std::string name);
	~ve_window();

	ve_window(const ve_window&) = delete;
	ve_window& operator=(const ve_window&) = delete;

	bool shouldClose() {
		return glfwWindowShouldClose(window);
	};

	VkExtent2D getExtend() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }

	void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

private:
	void initWindow();

	const int width;
	const int height;

	std::string windowName;
	GLFWwindow* window;
};

} // namespace ve