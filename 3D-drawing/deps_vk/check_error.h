#pragma once
#include "vulkan/vulkan.h"

bool vk_check_result(const VkResult);
bool glfw_check_result(const VkResult);
//bool could be const except not necessary -- compiler ignored
