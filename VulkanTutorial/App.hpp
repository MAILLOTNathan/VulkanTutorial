//
//  my.hpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 06/03/2025.
//

#ifndef _ETIB_APP_HPP_
#define _ETIB_APP_HPP_

    #include <vulkan/vulkan.h>
    #include "Utils.hpp"
    #include "Version.hpp"

#ifdef _WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
#endif

    #define GLFW_INCLUDE_VULKAN
    #include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#endif

    #include <glm/glm.hpp>
    #include <GLFW/glfw3native.h>

    #include <iostream>
    #include <stdexcept>
    #include <cstdlib>
    #include <map>
    #include <optional>
    #include <set>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    "VK_KHR_portability_subset"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

class App {
    public:
        App(const std::string &name, const Version &version, const std::string &engineName, const Version &engineVersion);
        App(const std::string &pathToConfig);
        ~App();

        void run();
    
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
    
        struct Vertex {
            glm::vec2 pos;
            glm::vec3 color;
            
            static VkVertexInputBindingDescription getBindingDescription() {
                VkVertexInputBindingDescription bindingDescription{};
                bindingDescription.binding = 0;
                bindingDescription.stride = sizeof(Vertex);
                bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                return bindingDescription;
            }
            
            static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
                std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

                attributeDescriptions[0].binding = 0;
                attributeDescriptions[0].location = 0;
                attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
                attributeDescriptions[0].offset = offsetof(Vertex, pos);

                attributeDescriptions[1].binding = 0;
                attributeDescriptions[1].location = 1;
                attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[1].offset = offsetof(Vertex, color);

                return attributeDescriptions;
            }
        };

    protected:
        GLFWwindow *_window;
        VkSurfaceKHR _surface;
        VkInstance _instance;
        VkRenderPass _renderPass;
        VkPipelineLayout _pipelineLayout;
        VkPipeline _graphicsPipeline;

        std::vector<VkFramebuffer> _swapChainFramebuffers;
        VkCommandPool _commandPool;
        std::vector<VkCommandBuffer> _commandBuffers;
    
        VkBuffer _vertexBuffer;
        VkDeviceMemory _vertexBufferMemory;
        VkBuffer _indexBuffer;
        VkDeviceMemory _indexBufferMemory;
    
        std::vector<VkSemaphore> _imageAvailableSemaphores;
        std::vector<VkSemaphore> _renderFinishedSemaphores;
        std::vector<VkFence> _inFlightFences;
        uint32_t _currentFrame = 0;
    
        VkSwapchainKHR _swapChain;
        std::vector<VkImage> _swapChainImages;
        VkFormat _swapChainImageFormat;
        VkExtent2D _swapChainExtent;
        std::vector<VkImageView> _swapChainImageViews;

        VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
        VkDevice _logicalDevice;
    
        VkQueue _graphicsQueue;
        VkQueue _presentQueue;

        VkDebugUtilsMessengerEXT _debugMessenger;
    
        std::string _appName;
        Version *_appVersion;
        std::string _engineName;
        Version *_engineVersion;
    
    private:
        // Initialization
        void initWindow();
        void initVulkan();
        
        // Debug
        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    
        // Routine
        void mainLoop();
        void cleanup();

        // Instance
        void createInstance();
    
        // Surface
        void createSurface();
    
        // Devices
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        void createLogicalDevice();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    
        // Queue Families
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        // Validation layers (not available on MacOS)
        bool checkValidationLayerSupport();
    
        // Swap Chain
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void createSwapChain();
        void createImageViews();
        void recreateSwapChain();
        void cleanupSwapChain();
    
        // Pipeline
        void createGraphicsPipeline();
    
        // Shaders
        VkShaderModule createShaderModule(const std::vector<char>& code);
    
        // Render Passes
        void createRenderPass();

        // Framebuffers
        void createFramebuffers();
    
        // Command
        void createCommandPool();
        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    
        // Drawing
        void drawFrame();
        void createSyncObjects();
    
        // Vertex
        void createVertexBuffer();
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void createIndexBuffer();
};

#endif
