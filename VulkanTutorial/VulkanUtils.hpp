//
//  VulkanUtils.hpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 14/03/2025.
//

#ifndef ETIB_VULKAN_UTILS
    #define ETIB_VULKAN_UTILS

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>

namespace Utils {
    class Vulkan {
        public:
            struct CreateBufferOption {
                VkDeviceSize size = 0;
                VkBufferUsageFlags usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
                VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
                VkBuffer& buffer;
                VkDeviceMemory& bufferMemory;
                VkDevice logicalDevice = VK_NULL_HANDLE;
                VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            };
        
            struct CopyBufferOption {
                VkBuffer srcBuffer = VK_NULL_HANDLE;
                VkBuffer dstBuffer = VK_NULL_HANDLE;
                VkDeviceSize size = 0;
                VkCommandPool commandPool = VK_NULL_HANDLE;
                VkDevice device = VK_NULL_HANDLE;
                VkQueue graphicsQueue = VK_NULL_HANDLE;
            };

            static void createBuffer(struct CreateBufferOption option);
            static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice device);
            static void copyBuffer(struct CopyBufferOption);
            static VkCommandBuffer beginSingleTimeCommands(VkDevice device, VkCommandPool commandPool);
            static void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue graphicsQueue, VkDevice device, VkCommandPool commandPool);
    };
}

#endif
