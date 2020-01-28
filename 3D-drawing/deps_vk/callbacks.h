#pragma once
#include <vulkan/vulkan.h>    //required for the vulkan callbacks
#include "vulkan_instance.h"  //required for the extern camera define there
                              //works without including it -- have not idea why

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}



void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

void scroll_callback(GLFWwindow* window, double xoff, double yoff) {
	//this is in need of some major fixing
#ifdef _WIN32
	camera.MovementSpeed += (float)yoff / 10000;
#else
#ifdef vsync
	camera.MovementSpeed += (float)yoff / 1000;
#else
	camera.MovementSpeed += (float)yoff / 100000;
#endif
#endif
	if (camera.MovementSpeed < 0.001f) camera.MovementSpeed = 0.001f;
}


bool window_firstMouse = true;
float window_last_x, window_last_y;
float xoffset, yoffset;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {

		if (window_firstMouse) {
			window_last_x = (float)xpos;
			window_last_y = (float)ypos;
			window_firstMouse = false;
		}

		xoffset = (float)xpos - window_last_x;
		yoffset = window_last_y - (float)ypos;

		window_last_x = (float)xpos;
		window_last_y = (float)ypos;
		camera.processMouse(xoffset, yoffset);
	}
	else {
		window_firstMouse = true;
	}
}
