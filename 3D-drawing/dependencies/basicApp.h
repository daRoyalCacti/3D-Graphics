#pragma once
#include <vector>
#include <cstring>
#include <optional>
#include <array>
#include <thread>
#include "global.h"
#include "vertex.h"
#include "Pixels.h"
#include "Buffer.h"
//#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "data.h"


const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
	"VK_KHR_swapchain"
};



#ifdef NODEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);



void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};




class basicApp {
public:
	void run();

	void initWindow();

	void initVulkan();
	void mainLoop();
	void cleanup();

	int no_mesh;
	int no_m_mesh;

private:
	VkDescriptorPool descriptorPool;

	ubo_model *square_model;// = new glm::mat4[no_meshes];

	//staticSimpleMesh Squares[no_images];
	staticSimpleMesh *staticMeshes; //= new staticSimpleMesh[no_images];
	moving_simple_mesh *movingMeshes;

	pixels *imagePixels;// = new pixels[no_images];

	#ifdef precalculated_player_camera
		glm::vec3 camera_positions[no_camera_positions];
		float camera_yaws[no_camera_positions];
		float camera_pitchs[no_camera_positions];
	#endif



	GLFWwindow* window;

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;

	VkDevice device;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;


	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;


	std::vector<VkImageView> swapChainImageViews;


	VkRenderPass renderPass;


	VkDescriptorSetLayout descriptorSetLayout;

	VkPipelineLayout pipelineLayout;


	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> swapChainFramebuffers;


	VkCommandPool commandPool;

	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;

	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;


	VkSampler textureSampler;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	size_t currentFrame = 0;

	bool framebufferResized = false;

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	void loadData();

	void recreateSwapChain();

	void drawFrame();

	void updateUniformBuffers(uint32_t currentImage);

	void cleanupSwapChain();

	void createInstance();

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	void setupDebugMessenger();

	void createSurface();

	void pickPhysicalDevice();

	void createLogicalDevice();

	void createSwapChain();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	void createImageViews();

	void createRenderPass();

	void createDescriptorSetLayout();

	void createGraphicsPipeline();

	void createFramebuffers();

	void createCommandPool();

	void createDepthResources();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	VkFormat findDepthFormat();

	void createTextureImage();


	void createTextureImageView();

	void createTextureSampler();

	void createVertexBuffer();

	void updateVertexBuffer(VkBuffer stagingBuffer, VkDeviceMemory stagingBufferMemory, VkDeviceSize bufferSize, VkBuffer vertexBuffer, std::vector<Vertex> vertices);

	void createIndexBuffer();

	void createUniformBuffers();

	void createDescriptorPool();

	void createDescriptorSets();


	void createCommandBuffers();

	void createSyncObjects();


	bool isDeviceSuitable(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	std::vector<const char*> getRequiredExtensions();

	bool checkValidationLayerSupport() ;

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	//void loadAssets(); //---------------------add-------------------------
	//will load model and textures







};
