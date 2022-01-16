#pragma once

#include "ve_camera.hpp"
#include "ve_game_object.hpp"

// lib
#include <vulkan/vulkan.h>

namespace ve {

	struct frame_info {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		ve_camera& camera;
		VkDescriptorSet globalDescriptorSet;
		ve_game_object::Map& gameObjects;
	};

} // namespace ve