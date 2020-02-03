#include "staging_buffer.h"
#include "vulkan_help.h"
#include <cstring>
#include <iostream>
//There might be better suited to be header only -- i haven't decided yet
namespace GBF {
	stagingBufferObject::stagingBufferObject() {
		stagingBuffer.buffer = &stagingBufferBuffer;
		stagingBuffer.memory = &stagingBufferMemory;
	}

	void stagingBufferObject::cleanup(VkDevice device) {
		vkDestroyBuffer(device, stagingBufferBuffer, nullptr);
		vkFreeMemory(device, stagingBufferMemory, nullptr);
	}

	void stagingBufferObject::create_buffer_vertex(VkDeviceSize bufferSize, VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer* buffer,
		VkDeviceMemory* bufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<Vertex> vertices) {


		Buffer buffer_raw(buffer, bufferMemory, bufferSize);
		stagingBuffer.size = bufferSize;

		stagingBuffer.create(device, physicalDevice, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		buffer_raw.create(device, physicalDevice, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);


		stagingBuffer.map(device);
		stagingBuffer.copy_mem(vertices.data());
		stagingBuffer.unmap(device);

		stagingBuffer.copy_buffer(device, commandPool, graphicsQueue, &buffer_raw);

	}

	void stagingBufferObject::updateVertexBuffer(VkDevice device, VkBuffer* buffer, std::vector<Vertex> vertices, VkCommandPool commandPool, VkQueue graphicsQueue) {
		stagingBuffer.map(device);
		stagingBuffer.copy_mem(vertices.data());
		stagingBuffer.unmap(device);

		stagingBuffer.copy_buffer(device, commandPool, graphicsQueue, buffer);
	}



	void stagingBufferObject::create_buffer_index(VkDeviceSize bufferSize, VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer* buffer,
		VkDeviceMemory* bufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<uint32_t> indices) {

		Buffer buffer_raw(buffer, bufferMemory, bufferSize);
		stagingBuffer.size = bufferSize;

		stagingBuffer.create(device, physicalDevice, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		buffer_raw.create(device, physicalDevice, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		stagingBuffer.map(device);
		stagingBuffer.copy_mem(indices.data());
		stagingBuffer.unmap(device);

		stagingBuffer.copy_buffer(device, commandPool, graphicsQueue, &buffer_raw);

	}


	void stagingBufferObject::create_buffer_image(int texWidth, int texHeight, VkDevice device, VkPhysicalDevice physicalDevice, VkImage* textureImage,
		VkDeviceMemory* textureImageMemory, VkCommandPool commandPool, VkQueue graphicsQueue, uint8_t* pixels) {

		VkDeviceSize imageSize = texWidth * texHeight * 4;

		stagingBuffer.size = imageSize;
		stagingBuffer.create(device, physicalDevice, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		stagingBuffer.map(device);
		stagingBuffer.copy_mem(pixels);
		stagingBuffer.unmap(device);

		delete [] pixels;

		createImage(device, physicalDevice, texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, *textureImage, *textureImageMemory);

		transitionImageLayout(device, commandPool, graphicsQueue, *textureImage, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		copyBufferToImage(device, commandPool, graphicsQueue, reinterpret_cast<VkBuffer>(*stagingBuffer.buffer), *textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
		transitionImageLayout(device, commandPool, graphicsQueue, *textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	}
}
