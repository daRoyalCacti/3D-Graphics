#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "vertex.h"
#include "Buffer.h"
#include <cstdint>

namespace GBF {
	struct stagingBufferObject {
		VkBuffer stagingBufferBuffer;
		VkDeviceMemory stagingBufferMemory;
		Buffer stagingBuffer;

		stagingBufferObject();

		void cleanup(VkDevice);

		void create_buffer_vertex(VkDeviceSize bufferSize, VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer* buffer,
			VkDeviceMemory* bufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<Vertex> vertices);

		void create_buffer_index(VkDeviceSize bufferSize, VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer* buffer,
			VkDeviceMemory* bufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<uint32_t> indices);

		void create_buffer_image(int texWidth, int texHeight, VkDevice device, VkPhysicalDevice physicalDevice, VkImage* textureImage,
			VkDeviceMemory* textureImageMemory, VkCommandPool commandPool, VkQueue graphicsQueue, uint8_t* pixels);

		void updateVertexBuffer(VkDevice device, VkBuffer* buffer, std::vector<Vertex> vertices, VkCommandPool commandPool, VkQueue graphicsQueue);
	};
}
