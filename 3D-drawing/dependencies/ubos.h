#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};

struct UniformBuffer {
	UniformBufferObject ubo;
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	uint32_t size;

	void create(VkDevice device, VkPhysicalDevice physicalDevice);
	void cleanup_swapChain(VkDevice device);
	void update(uint32_t currentImage, VkDevice device);
};


struct ubo_model {
	std::vector<glm::mat4> models;
	unsigned total_frames;
	bool modulous = false;
	ubo_model(){};
	ubo_model(unsigned frames) : total_frames(frames) {};
	glm::mat4 frame(unsigned frame_num);
};
