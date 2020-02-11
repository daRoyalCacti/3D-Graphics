#include "check_error.h"
#include <iostream>
#include "global.h"

//false == error, true == success
bool vk_check_result(const VkResult result) {
  //different error checking for release mode
  #ifdef NODEBUG
  if (result >= 0) { //by the vulkan spec all VkResult's >=0 are successes
    return true;
  }
  #endif

  #ifndef NODEBUG
  //likely results first
  if (result == VK_SUCCESS) {
    return true;
  }

  if (result == VK_ERROR_OUT_OF_HOST_MEMORY) {
    std::cerr << "Host is out of memory" << std::endl;
    return false;
  }
  if (result == VK_ERROR_OUT_OF_DEVICE_MEMORY) {
    std::cerr << "Device is out of memory" << std::endl;
    return false;
  }

  //success functions
  if (result == VK_TIMEOUT) {
    std::cerr << "A wait operation (likely fences) has not completed in the specified time" << std::endl;
    return true;
  }
  if (result == VK_NOT_READY) {
    std::cerr << "A fence or query has not been completed" << std::endl;
    return true;
  }
  if (result == VK_SUBOPTIMAL_KHR) {
    std::cerr << "A swapchain no longer matches the surface properties exactly\n\tThe swapchain can still be used to success present to however" << std::endl;
    return true;
  }

  //error function
  if (result == VK_ERROR_DEVICE_LOST) {
    std::cerr << "The physical or logical device is lost" << std::endl;
    std::cerr << "see    https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#devsandqueues-lost-device   for details" << std::endl;
    //spaces above to make a clear distinction between link and text
    return false;
  }
  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
    std::cerr << "The swap chain has become incompatble with the surface\n\tFurther presntations requests to the swapchain will fail" << std::endl;
    std::cerr << "This usually happens after a window resize" << std::endl;
    return false;
  }
  if (result == VK_ERROR_SURFACE_LOST_KHR) {
    std::cerr << "A surface is no longer available" << std::endl;
    return false;
  }
  if (result == VK_ERROR_INITIALIZATION_FAILED) {
    std::cerr << "Initialization of an object could not be completed\n\tThis is because of implementation-specific reasons" << std::endl;
    return false;
  }
  if (result == VK_ERROR_LAYER_NOT_PRESENT) {
    std::cerr << "A requested layer is not present or could not be loaded" << std::endl;  //not sure what layer is being refered to
                                                                                          //-- error code take from https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCreateInstance.html
    return false;
  }
  if (result == VK_ERROR_EXTENSION_NOT_PRESENT) {
    std::cerr << "A requested extension is not supported" << std::endl;
    return false;
  }
  if (result == VK_ERROR_FEATURE_NOT_PRESENT) {
    std::cerr << "A requested feature is not supported" << std::endl;
    return false;
  }
  if (result == VK_ERROR_INCOMPATIBLE_DRIVER) {
    std::cerr << "The requested version of Vulkan is not supported by the driver" << std::endl;
    std::cerr << "This could also happen because of implementation-specific reasons" << std::endl;
    return false;
  }
  if (result == VK_ERROR_TOO_MANY_OBJECTS) {
    std::cerr <<  "Too many objects of the same type have already been created" << std::endl;
    std::cerr << "\tCheck where error was called to see what objects" << std::endl;   //haven't checked
    return false;
  }
  if (result == VK_ERROR_INVALID_SHADER_NV) {
    std::cerr << "One or more shaders failed to compile or link" << std::endl;
    return false;
  }
  if (result == VK_ERROR_FRAGMENTATION_EXT) {
    std::cerr << "A descriptor pool creation has failed due to fragmentation" << std::endl; //no idea what fragmentation is
                                                                                            //related def? - The scattering of parts of a file or files throughout a storage device, as when the operating system breaks up the file and fits it into the spaces left vacant by previously deleted files
    return false;
  }



  if (result == VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT) {
    std::cerr << "An operation on the swapchain failed because it did not have exclusive full-screen access" << std::endl;
    return false;
  }

  #endif

  std::cout << "The result is not known\nResult code: " << result << std::endl;
  std::cout << "see    https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkResult.html   for details" << std::endl;

  if (result > 0) { //by the vulkan spec all VkResult's >=0 are successes
    return true;
  } else {
    return false;
  }
}


//all error codes are usable in the function above, but glfw api calls are made as well so those need to be logges as well
bool glfw_check_result(const VkResult result) {
  if (result == VK_SUCCESS) {
    return true;
  }
  if (result == VK_ERROR_INITIALIZATION_FAILED) {
    //vulkan error followed by glfw error
    std::cerr << "The Vulkan loader or at least one minimally functional ICD were not found" << std::endl;
    std::cerr << "The installed graphics driver does not support Vulkan, or the graphics driver does not support it via the chose context creation backend\n\tor there was some other error" << std::endl;
    return false;
  }
  if (result == VK_ERROR_EXTENSION_NOT_PRESENT) {
    //vulkan error followed by glfw error
    std::cerr << "The required window surface creation instance extensions are not available,  or teh specifed instance was not created with these extensions enabled" << std::endl;
    std::cerr << "The installed graphics driver does not support Vulkan, or the graphics driver does not support it via the chose context creation backend\n\tor there was some other error" << std::endl;
    return false;
  }
  if (result == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) {
    //vulkan error
    std::cerr << "The window was not generated using GLFW_NO_API" << std::endl;
    return false;
  }

  return false; //will only return true on VK_SUCCESS
}
