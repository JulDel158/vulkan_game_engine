#pragma once

#include "ve_device.hpp"

#include <string>
#include <vector>

namespace ve {

struct PipelineCongfigInfo {
	VkViewport viewport;
	VkRect2D scissor;
	VkPipelineViewportStateCreateInfo viewportInfo;
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
	VkPipelineRasterizationStateCreateInfo rasterizationInfo;
	VkPipelineMultisampleStateCreateInfo multisampleInfo;
	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo colorBlendInfo;
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
	VkPipelineLayout pipelineLayout = nullptr;
	VkRenderPass renderPass = nullptr;
	uint32_t subpass = 0;
};

class VePipeline {
public:
	VePipeline(
		ve_device& device,
		const std::string& vertFilepath, 
		const std::string& fragFilepath,
		const PipelineCongfigInfo& configInfo);

	~VePipeline();

	VePipeline(const VePipeline&) = delete;
	VePipeline& operator=(const VePipeline&) = delete;

	static PipelineCongfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

private:
	static std::vector<char> readFile(const std::string& filepath);

	void createGraphicsPipeline(
		const std::string& vertFilepath, 
		const std::string& fragFilepath, 
		const PipelineCongfigInfo& configInfo);

	void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

	ve_device& veDevice;
	VkPipeline graphicsPipeline;
	VkShaderModule vertShaderModule;
	VkShaderModule fragShaderModule;
};

} // namespace ve