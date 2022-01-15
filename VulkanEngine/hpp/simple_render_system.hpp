#pragma once

#include "ve_device.hpp"
#include "ve_game_object.hpp"
#include "ve_pipeline.hpp"

// std
#include <memory>
#include <vector>

namespace ve {

	class simple_render_system {
	public:
		simple_render_system(ve_device& device, VkRenderPass renderPass);
		~simple_render_system();

		simple_render_system(const simple_render_system&) = delete;
		simple_render_system& operator=(const simple_render_system&) = delete;

		void renderGameObjects(VkCommandBuffer commandBuffer, 
			std::vector<ve_game_object> &gameObjects);

	private:
		void createPipelineLayout();
		void createPipeline(VkRenderPass renderPass);
		
		ve_device& veDevice;

		std::unique_ptr<ve_pipeline> vePipeline;
		VkPipelineLayout pipelineLayout;
	};


} // namespace ve