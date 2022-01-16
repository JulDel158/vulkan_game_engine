#pragma once

#include "ve_camera.hpp"

// lib
#include <vulkan/vulkan.h>

namespace ve {

	struct frame_info {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		ve_camera& camera;
		VkDescriptorSet globalDescriptorSet;
	};

} // namespace ve