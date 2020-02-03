#include "ubos.h"
#include "vulkan_help.h"
#include <iostream>
#include <cstring>

void UniformBuffer::create(VkDevice device, VkPhysicalDevice physicalDevice){
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);
	uniformBuffers.resize(size);
    uniformBuffersMemory.resize(size);
    for (size_t i = 0; i < size; i++) {
        createBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        	uniformBuffers[i], uniformBuffersMemory[i]);
    }

}

void UniformBuffer::cleanup_swapChain(VkDevice device){
	for (size_t i = 0; i < size; i++) {
        vkDestroyBuffer(device, uniformBuffers[i], nullptr);
        vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
    }
}

void UniformBuffer::update(uint32_t currentImage, VkDevice device){
	ubo.proj[1][1] *= -1;
	void* data;
    vkMapMemory(device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(device, uniformBuffersMemory[currentImage]);
}


//pure on request of the compiler
__attribute__((pure)) glm::mat4 ubo_model::frame(unsigned frame_num) {
		if (modulous) {
			return models[frame_num % (total_frames)];
		} else {
			if (frame_num > total_frames) {
				return models[total_frames - 1];
			} else {
				return models[frame_num];
			}
		}
}
