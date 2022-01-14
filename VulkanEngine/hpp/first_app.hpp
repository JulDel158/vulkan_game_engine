#pragma once

#include "ve_window.hpp"
#include "ve_pipeline.hpp"
#include "ve_swap_chain.hpp"
#include "ve_device.hpp"
#include "ve_model.hpp"

#include <memory>
#include <vector>

namespace ve {

class FirstApp {
public:
	static constexpr int WIDTH = 800;
	static constexpr int HEIGHT = 600;

	FirstApp();
	~FirstApp();

	FirstApp(const FirstApp&) = delete;
	FirstApp& operator=(const FirstApp&) = delete;

	void run();
private:
	void loadModels();
	void createPipelineLayout();
	void createPipeline();
	void createCommandBuffers();
	void freeCommandBuffers();
	void drawFrame();
	void recreateSwapChain();
	void recordCommandBuffer(int imageIndex);

	ve_window veWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
	ve_device veDevice{ veWindow };
	std::unique_ptr<ve_swap_chain> veSwapChain;
	std::unique_ptr<ve_pipeline> vePipeline;
	VkPipelineLayout pipelineLayout;
	std::vector<VkCommandBuffer> commandBuffers;
	std::unique_ptr<ve_model> veModel;
};


} // namespace ve