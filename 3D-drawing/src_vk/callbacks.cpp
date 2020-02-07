//this is essentially where any function that MUST have an unused parameter is defined
// - this will mainly happen in callback functions for given libraries and hence the files name

#include "callbacks.h"     //main header
//#include "GLFW/glfw3.h"
#include <iostream>
#include "global.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
//callbacks by their nature are going to have a lot of unused parameters

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
/*#ifdef _WIN32
	camera.MovementSpeed += (float)yoff / 10000; //camera is defined globally
#else
#ifdef vsync
	camera.MovementSpeed += (float)yoff / 1000;
#else
	camera.MovementSpeed += (float)yoff / 100000;
#endif
#endif*/
  global::camera.targetSpeed += (float)yoff;
	if (global::camera.targetSpeed < 0.001f) global::camera.targetSpeed = 0.001f;
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
		global::camera.processMouse(xoffset, yoffset);
	}
	else {
		window_firstMouse = true;
	}
}

void vulkanApp::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto app = reinterpret_cast<vulkanApp*>(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
}


VKAPI_ATTR VkBool32 VKAPI_CALL vulkanApp::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) { //callback for when a validation layer throws and error
	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl; 	//just write the error to standard output
																																							//should probably have if statements for message severity

	return VK_FALSE;
}
#pragma GCC diagnostic pop
