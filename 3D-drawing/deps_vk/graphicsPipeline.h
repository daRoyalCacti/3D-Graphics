#pragma once
#include "vulkan/vulkan.h"
#include <string>
#include <array>

namespace GB {
	inline VkPipelineShaderStageCreateInfo createVertexShaderInfo(VkShaderModule shadermod) {

		VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = shadermod;
		vertShaderStageInfo.pName = "main";

		return vertShaderStageInfo;
	}

	inline VkShaderModule shaderModule(VkDevice device, std::string shader_loc) {
		auto vertShaderCode = readFile(shader_loc);

		return createShaderModule(device, vertShaderCode);
	}

	inline VkPipelineShaderStageCreateInfo createFragmentShaderInfo(VkShaderModule shadermod) {
		VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = shadermod;
		fragShaderStageInfo.pName = "main";

		return fragShaderStageInfo;
	}

	inline VkPipelineVertexInputStateCreateInfo vertexInfoInput(VkVertexInputBindingDescription* bindingDescription, std::array<VkVertexInputAttributeDescription, 2> *attributeDescriptions){
		//needs updating

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions->size());
		vertexInputInfo.pVertexBindingDescriptions = bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions->data();

		return vertexInputInfo;
	}

	inline VkPipelineInputAssemblyStateCreateInfo assemblyInput(VkPrimitiveTopology topolgy) {
		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = topolgy;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		return inputAssembly;
	}

	inline VkViewport createViewport(float xoff, float yoff, float xfrac, float yfrac, VkExtent2D swapChainExtent) {
		VkViewport viewport = {};
		viewport.x = (float)swapChainExtent.width * xoff;
		viewport.y = (float)swapChainExtent.height * yoff;
		viewport.width = (float)swapChainExtent.width * xfrac;
		viewport.height = (float)swapChainExtent.height * yfrac;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		return viewport;
	}

	inline VkRect2D createScissor(float xoff, float yoff, float xfrac, float yfrac, VkExtent2D swapChainExtent) {
		VkRect2D scissor = {};
		scissor.offset = { (int32_t)(swapChainExtent.width * xoff), (int32_t)(swapChainExtent.height * yoff) };
		scissor.extent.width = static_cast<uint32_t>(swapChainExtent.width * xfrac);
		scissor.extent.height = static_cast<uint32_t>(swapChainExtent.height * yfrac);

		return scissor;
	}

	inline VkPipelineViewportStateCreateInfo createViewportState(VkViewport* viewport, VkRect2D* scissor) {
		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = scissor;

		return viewportState;
	}

	inline VkPipelineRasterizationStateCreateInfo createRasterizer(VkPolygonMode polygonMode, VkCullModeFlags cullMode, VkFrontFace frontFace) {
		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = polygonMode;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = cullMode;
		rasterizer.frontFace = frontFace;
		rasterizer.depthBiasEnable = VK_FALSE;

		rasterizer.depthBiasConstantFactor = 0.0f;
		rasterizer.depthBiasClamp = 0.0f;
		rasterizer.depthBiasSlopeFactor = 0.0f;

		return rasterizer;
	}

	inline VkPipelineMultisampleStateCreateInfo multisamplingInfo() {
		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling.minSampleShading = 1.0f;
		multisampling.pSampleMask = nullptr;
		multisampling.alphaToCoverageEnable = VK_FALSE;
		multisampling.alphaToOneEnable = VK_FALSE;

		return multisampling;
	}

	inline VkPipelineDepthStencilStateCreateInfo depthStencilInfo() {
		VkPipelineDepthStencilStateCreateInfo depthStencil;
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = VK_TRUE;
		depthStencil.depthWriteEnable = VK_TRUE;
		depthStencil.depthCompareOp = 	VK_COMPARE_OP_LESS_OR_EQUAL;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		depthStencil.minDepthBounds = 0.0f;
		depthStencil.maxDepthBounds = 1.0f;
		depthStencil.stencilTestEnable = VK_FALSE;
		depthStencil.front = {};
		depthStencil.back = {};
		depthStencil.pNext = nullptr;
		depthStencil.flags = 0;

		return depthStencil;
	}

	inline VkPipelineColorBlendAttachmentState  colorBlendAttachmentInfo() {
		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		//VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional


		return colorBlendAttachment;
	}

	inline VkPipelineColorBlendStateCreateInfo colorBlendStateInfo(VkPipelineColorBlendAttachmentState* colorBlendAttachment) {
		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;


		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = colorBlendAttachment;

		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;


		return colorBlending;
	}

	inline VkPipelineLayoutCreateInfo createPipelineLayoutInfo(VkDescriptorSetLayout* descriptorSetLayout) {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 1; //change?
		pipelineLayoutInfo.pSetLayouts = descriptorSetLayout;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		return pipelineLayoutInfo;
	}
}
