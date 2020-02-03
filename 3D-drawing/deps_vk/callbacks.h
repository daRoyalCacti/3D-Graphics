#pragma once
#include <vulkan/vulkan.h>    //required for the vulkan callbacks
#include "vulkan_instance.h"  //a couple of functions defined here are callbacks

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

void scroll_callback(GLFWwindow* window, double xoff, double yoff);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
