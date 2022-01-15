#pragma once

#include "ve_device.hpp"
#include "ve_swap_chain.hpp"
#include "ve_window.hpp"

// std
#include <cassert>
#include <memory>
#include <vector>

namespace ve {

	class ve_renderer {
	public:
		ve_renderer(ve_window &veWindow, ve_device &veDevice);
		~ve_renderer();

		ve_renderer(const ve_renderer&) = delete;
		ve_renderer& operator=(const ve_renderer&) = delete;

		VkRenderPass getSwapChainRenderPass() const { return veSwapChain->getRenderPass(); }

		bool isFrameInProgress() const { return isFrameStarted; }

		VkCommandBuffer getCurrentCommandBuffer() const {
			assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
			return commandBuffers[currentFrameIndex];
		}

		int getFraneIndex() const {
			assert(isFrameStarted && "Cannot get frame index when frame not in progress");
			return currentFrameIndex;
		}

		VkCommandBuffer beginFrame();
		void endFrame();
		void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

	private:
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();

		ve_window& veWindow;
		ve_device& veDevice;
		std::unique_ptr<ve_swap_chain> veSwapChain;
		std::vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex;
		int currentFrameIndex{ 0 };
		bool isFrameStarted{ false };
	};


} // namespace ve