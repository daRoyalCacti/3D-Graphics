#pragma once
#include "vulkan/vulkan.h"

inline VkDescriptorSetLayoutBinding uboDescriptorLayoutBinding(int binding){
	//need to update to include if for vertex or fragment shader
	VkDescriptorSetLayoutBinding uboLayoutBinding = {};
	uboLayoutBinding.binding = binding;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.descriptorCount = 1; //used for array of ubos
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	uboLayoutBinding.pImmutableSamplers = nullptr;

	return uboLayoutBinding;
}
//need to update to include if for vertex or fragment shader

inline VkDescriptorSetLayoutBinding samplerDescriptorLayoutBinding(int binding){
	//need to update to include if for vertex or fragment shader
	VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
	samplerLayoutBinding.binding = binding;
	samplerLayoutBinding.descriptorCount = 1;
	samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerLayoutBinding.pImmutableSamplers = nullptr;
	samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	return samplerLayoutBinding;
}
//need to update to include if for vertex or fragment shader

inline VkDescriptorSetLayoutBinding uboLightDescriptorLayoutBinding(int binding) {
	VkDescriptorSetLayoutBinding uboLayoutBinding = {};
	uboLayoutBinding.binding = binding;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.descriptorCount = 1; //used for array of ubos
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
	uboLayoutBinding.pImmutableSamplers = nullptr;

	return uboLayoutBinding;
}
