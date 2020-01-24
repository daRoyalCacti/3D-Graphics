#pragma once
#include <stb_image.h>
#include "vulkan/vulkan.h"
#include <string>
#include "Pixels.h"
#include "staging_buffer.h"

class texture {
public:
	texture() {}
	inline void cleanup(VkDevice device) {
		vkDestroyImage(device, textureImage, nullptr);
		vkFreeMemory(device, textureImageMemory, nullptr);
		vkDestroyImageView(device, textureImageView, nullptr);
	}

	inline void create(std::string file, VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue) {
		pixels imagePixels;

		imagePixels.read_file(file.c_str());

		GBF::stagingBufferObject sb;
		sb.create_buffer_image(imagePixels.texWidth, imagePixels.texHeight, device, physicalDevice, &textureImage, &textureImageMemory, commandPool, graphicsQueue, imagePixels.pixels);

		sb.cleanup(device);
	}

	inline void create(pixels imagePixels, VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue) {

		GBF::stagingBufferObject sb;
	#pragma omp critical
		{
		sb.create_buffer_image(imagePixels.texWidth, imagePixels.texHeight, device, physicalDevice, &textureImage, &textureImageMemory, commandPool, graphicsQueue, imagePixels.pixels);
		}

		sb.cleanup(device); //WIP
	}

	inline void createView(VkDevice device) {
		textureImageView = createImageView(device, textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
	}
	//void cleanup_creation(VkDevice device);

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	//stagingBufferObject sb_;
};
