#pragma once

#include "ve_window.hpp"

namespace ve {

class FirstApp {
public:
	static constexpr int WIDTH = 800;
	static constexpr int HEIGHT = 600;

	void run();
private:
	ve_window veWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
};


} // namespace ve