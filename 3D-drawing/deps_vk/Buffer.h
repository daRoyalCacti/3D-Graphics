#pragma once
#include "vulkan_help.h"
#include <iostream>
#include <assert.h>
#include <cstring>
#include "vulkan/vulkan.h"
 
namespace GBF {
	struct Buffer {
		//this is a simple wrapper around some helper functions
		//the structs primary purpose is the make coding
		VkBuffer* buffer = nullptr; //the buffer that this struct is refering to
		VkDeviceMemory* memory = nullptr; //the buffer requires its own memory
				//values are pointers because they are only used to be passesd into functions and this made coding it easier

		VkDeviceSize size = 0;
		VkDeviceSize offset = 0;
				//these values will rarely be touched but exist just incase there is a circumstance where they are needed

		void* mapped = nullptr;

		Buffer() {} //this constructor is for when it is convenient to set the comonents using dot notation
		Buffer(VkBuffer* buffer_, VkDeviceMemory* memory_ = VK_NULL_HANDLE, VkDeviceSize size_ = 0, VkDeviceSize offset_ = 0) : buffer(buffer_), memory(memory_), size(size_), offset(offset_) { }
			//order of variables initialised must line up with order they are declared

		inline void create(VkDevice device, VkPhysicalDevice physicalDevice, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) {
			//this calls the create buffer function from 'vulkan_help.h'
			//it is obviously used to create the buffer -- for infomation see the comments in the code for the function
			createBuffer(device, physicalDevice, size, usage, properties, *buffer, *memory);
		}

		inline void map(VkDevice device) {
			//the memory has to be mapped in order to copy data into the buffer
			vkMapMemory(device, *memory, 0, size, 0, &mapped);
		}

		inline void unmap(VkDevice device){
			//unmapping the mapped memory when it is no longer needed to save on device memory
			//leaving too much memory mapped can cause the program to break -- see https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkMapMemory.html
			if (mapped) {
				vkUnmapMemory(device, *memory);
				mapped = nullptr;
			}
		}

		inline void copy_mem(void* data) {
			//this is used to copy abitrary data into the buffer
			// - for example inside of stagingBufferObject, it is used to copy in the vertices, indices, and texture data
			assert(mapped);
			memcpy(mapped, data, (size_t)size);
		}

		inline void copy_buffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer* buffer2){
			//this copys the current buffer contents into another buffer
			//this is used extensively in stagingBufferObject to copy host memory buffers into device memroy buffers
			#pragma omp critical
			//critical needs to be moved inside of the "copyBuffer" function instead
			{
				copyBuffer(device, commandPool, graphicsQueue, *buffer, *buffer2, size);
			}
		}

		inline void copy_buffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, Buffer* buffer2){
			//same as the function above exact this function takes a buffer object instead of a VkBuffer object
			#pragma omp critical
			{
				copyBuffer(device, commandPool, graphicsQueue, *buffer, *buffer2->buffer, size);
			}
		}

		inline void cleaup(VkDevice device){
			//destroying the buffer and freeing the memory
			vkDestroyBuffer(device, *buffer, nullptr);
			vkFreeMemory(device, *memory, nullptr);
		}

	};
}
