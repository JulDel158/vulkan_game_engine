#pragma once

#include "ve_device.hpp"

#include <string>
#include <vector>

namespace ve {

struct PipelineConfigInfo {
	PipelineConfigInfo(const PipelineConfigInfo&) = delete;
	PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

	VkPipelineViewportStateCreateInfo viewportInfo;
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
	VkPipelineRasterizationStateCreateInfo rasterizationInfo;
	VkPipelineMultisampleStateCreateInfo multisampleInfo;
	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo colorBlendInfo;
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
	std::vector<VkDynamicState> dynamicStateEnables;
	VkPipelineDynamicStateCreateInfo dynamicStateInfo;
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
		const PipelineConfigInfo& configInfo);

	ve_pipeline() = default;
	~ve_pipeline();

	ve_pipeline(const ve_pipeline&) = delete;
	ve_pipeline &operator=(const ve_pipeline&) = delete;

	void bind(VkCommandBuffer commandBuffer);

	static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

private:
	static std::vector<char> readFile(const std::string& filepath);

	void createGraphicsPipeline(
		const std::string& vertFilepath, 
		const std::string& fragFilepath, 
		const PipelineConfigInfo& configInfo);

	void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

	ve_device& veDevice;
	VkPipeline graphicsPipeline;
	VkShaderModule vertShaderModule;
	VkShaderModule fragShaderModule;
};

} // namespace ve