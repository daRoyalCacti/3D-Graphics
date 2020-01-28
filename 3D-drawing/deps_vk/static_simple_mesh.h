#pragma once
#include <vector>
#include "vertex.h"
#include "ubos.h"
#include "staging_buffer.h"

#include <string>
#include "Texture.h"

void do_bar();

class staticSimpleMesh {
public:
	staticSimpleMesh(std::vector<Vertex> verts, std::vector<uint32_t> inds, bool);
	staticSimpleMesh();

	void createUb(uint32_t size, VkDevice device, VkPhysicalDevice physicalDevice);

	void cleanup_swapChain(VkDevice device);
	void cleanup(VkDevice device);

	void ubo_update(uint32_t currentImage, VkDevice device);

	void createDescriptorPool(VkDevice device);
	void createDescriptorSet(VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool *descriptorPool, VkDevice device, VkSampler textureSampler);

	void createTexture(std::string file, VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue);
	void createTexture(pixels pix, VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue);

	void createTextureImageView(VkDevice device);

	void draw(std::vector<VkCommandBuffer> commandBuffers, VkPipelineLayout pipelineLayout, size_t i);

	void createVertexBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkPhysicalDevice physicalDevice);

	void createIndexBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkPhysicalDevice physicalDevice);

	void updateVertexBuffer(VkDevice device, std::vector<Vertex> vertices, VkCommandPool commandPool, VkQueue graphicsQueue);

	void init(); //!! need to actually do

	void TextureCleanupCreation(VkDevice device);

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	UniformBuffer ub;

	bool staging;

private:
	float posx, posy, posz, length1, length2;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	GBF::stagingBufferObject sb;
	VkDeviceSize bufferSize;

	//VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
	VkImageView textureImageView;
	VkBuffer vertexBuffer;
	VkBuffer indexBuffer;
	texture tex;

	VkDeviceMemory vertexBufferMemory;
	VkDeviceMemory indexBufferMemory;

};
