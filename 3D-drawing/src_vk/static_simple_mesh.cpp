#include <iostream>
#include <cstring>
#include "static_simple_mesh.h"
#include "Pixels.h"
#include "Buffer.h"

#include "vulkan_help.h"

void do_bar() {
	std::cout << "no u r" << std::endl;
}

staticSimpleMesh::staticSimpleMesh(std::vector<Vertex> verts, std::vector<uint32_t> inds, bool stat = 1) {
	vertices = verts;
	indices = inds;
	staging = stat;
}


staticSimpleMesh::staticSimpleMesh() {
	staging = 1;
}

void staticSimpleMesh::createUb(uint32_t size, VkDevice device, VkPhysicalDevice physicalDevice){
	ub.size = size;
	ub.create(device, physicalDevice);

}

void staticSimpleMesh::cleanup_swapChain(VkDevice device) {
	ub.cleanup_swapChain(device);
	//vkDestroyDescriptorPool(device, descriptorPool, nullptr);
}

void staticSimpleMesh::cleanup(VkDevice device) {
	tex.cleanup(device);
	vkDestroyBuffer(device, vertexBuffer, nullptr);
	vkFreeMemory(device, vertexBufferMemory, nullptr);
	sb.cleanup(device);

	vkDestroyBuffer(device, indexBuffer, nullptr);
	vkFreeMemory(device, indexBufferMemory, nullptr);
}

void staticSimpleMesh::ubo_update(uint32_t currentImage, VkDevice device){
	ub.update(currentImage, device);
}

/*
void staticSimpleMesh::createDescriptorPool(VkDevice device){
	std::array<VkDescriptorPoolSize,2> poolSizes = {};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(ub.size);
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(ub.size);
	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(ub.size);
	if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}
*/


/*void staticSimpleMesh::createTexture(std::string file, VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue){
	tex.create(file, device, physicalDevice, commandPool, graphicsQueue);
}*/

void staticSimpleMesh::createTexture(pixels pix, VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue) {
	tex.create(pix, device, physicalDevice, commandPool, graphicsQueue);
}

void staticSimpleMesh::createTextureImageView(VkDevice device){
	tex.createView(device);
}
/*
void staticSimpleMesh::TextureCleanupCreation(VkDevice device) {
	tex.cleanup_creation(device);
}
*/


void staticSimpleMesh::createDescriptorSet(VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool* descriptorPool, VkDevice device, VkSampler textureSampler) {
	std::vector<VkDescriptorSetLayout> layouts(ub.size, descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = *descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(ub.size);
    allocInfo.pSetLayouts = layouts.data();

    descriptorSets.resize(ub.size);
    if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < ub.size; i++) {
        VkDescriptorBufferInfo bufferInfo = {};
        bufferInfo.buffer = ub.uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkDescriptorImageInfo imageInfo = {};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = tex.textureImageView;
        imageInfo.sampler = textureSampler;

        std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;
        descriptorWrites[0].pImageInfo = nullptr;
        descriptorWrites[0].pTexelBufferView = nullptr;

        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;

        vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
}


void staticSimpleMesh::draw(std::vector<VkCommandBuffer> commandBuffers, VkPipelineLayout pipelineLayout, size_t i) {
	VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

    vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);


	vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0,0);
	//vkCmdDraw(commandBuffers[i], static_cast<uint32_t>(vertices.size()), 1, 0, 0);

}


void staticSimpleMesh::createVertexBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkPhysicalDevice physicalDevice) {
	bufferSize = sizeof(vertices[0]) * vertices.size();

	if (staging){
		sb.create_buffer_vertex(bufferSize, device, physicalDevice, &vertexBuffer, &vertexBufferMemory, commandPool, graphicsQueue, vertices);
	} else {
    	createBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer, vertexBufferMemory);

		void* data;
    	vkMapMemory(device, vertexBufferMemory, 0, bufferSize, 0, &data);
    	memcpy(data, vertices.data(), (size_t) bufferSize);
    	vkUnmapMemory(device, vertexBufferMemory);
	}
}

void staticSimpleMesh::updateVertexBuffer(VkDevice device, std::vector<Vertex> _vertices, VkCommandPool commandPool, VkQueue graphicsQueue) {
	if (staging){
		sb.updateVertexBuffer(device, &vertexBuffer, _vertices, commandPool, graphicsQueue);
	} else {
		void* data;
    	vkMapMemory(device, vertexBufferMemory, 0, bufferSize, 0, &data);
    	memcpy(data, _vertices.data(), (size_t) bufferSize);
    	vkUnmapMemory(device, vertexBufferMemory);
	}

}


void staticSimpleMesh::createIndexBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkPhysicalDevice physicalDevice){

	VkDeviceSize _bufferSize = sizeof(indices[0]) * indices.size();

	GBF::stagingBufferObject _sb;

  _sb.create_buffer_index(_bufferSize, device, physicalDevice, &indexBuffer, &indexBufferMemory, commandPool, graphicsQueue, indices);
  _sb.cleanup(device);

}
