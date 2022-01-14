#include "../hpp/ve_window.hpp"

#include <stdexcept>

namespace ve {

	ve_window::ve_window(int w, int h, std::string name) : 
		width{ w },
		height{ h },
		windowName{ name } {
		initWindow();
	}

	ve_window::~ve_window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void ve_window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create window surface");
		}
	}

	void ve_window::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	}

	void ve_window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto veWindow = reinterpret_cast<ve_window*>(glfwGetWindowUserPointer(window));
		veWindow->framebufferResized = true;
		veWindow->width = width;
		veWindow->height = height;
	}

} // namespace ve