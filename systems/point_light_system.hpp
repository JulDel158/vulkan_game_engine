#pragma once

#include "ve_camera.hpp"
#include "ve_device.hpp"
#include "ve_frame_info.hpp"
#include "ve_game_object.hpp"
#include "ve_pipeline.hpp"

// std
#include <memory>
#include <vector>

namespace ve {

	class point_light_system {
	public:
		point_light_system(ve_device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
		~point_light_system();

		point_light_system(const point_light_system&) = delete;
		point_light_system& operator=(const point_light_system&) = delete;

		void render(frame_info &frameInfo);

	private:
		void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		void createPipeline(VkRenderPass renderPass);
		
		ve_device& veDevice;

		std::unique_ptr<ve_pipeline> vePipeline;
		VkPipelineLayout pipelineLayout;
	};


} // namespace ve