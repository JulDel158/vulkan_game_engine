#pragma once

#include "ve_window.hpp"
#include "ve_pipeline.hpp"

namespace ve {

class FirstApp {
public:
	static constexpr int WIDTH = 800;
	static constexpr int HEIGHT = 600;

	void run();
private:
	ve_window veWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
	VePipeline vePipeline{ "Shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv" };
};


} // namespace ve