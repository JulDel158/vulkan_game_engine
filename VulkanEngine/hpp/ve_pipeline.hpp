#pragma once

#include "ve_device.hpp"

#include <string>
#include <vector>

namespace ve {

struct PipelineCongfigInfo {
	VkViewport viewport;
	VkRect2D scissor;
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

class ve_pipeline {
public:
	ve_pipeline(
		ve_device& device,
		const std::string& vertFilepath, 
		const std::string& fragFilepath,
		const PipelineCongfigInfo& configInfo);

	~ve_pipeline();

	ve_pipeline(const ve_pipeline&) = delete;
	ve_pipeline& operator=(const ve_pipeline&) = delete;

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