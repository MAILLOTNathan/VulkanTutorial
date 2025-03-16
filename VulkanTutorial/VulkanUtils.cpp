//
//  VulkanUtils.cpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 14/03/2025.
//

#include "VulkanUtils.hpp"

void Utils::Vulkan::createBuffer(struct BufferOption option)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = option.size;
    bufferInfo.usage = option.usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(option.logicalDevice, &bufferInfo, nullptr, &option.buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(option.logicalDevice, option.buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, option.properties, option.physicalDevice);

    if (vkAllocateMemory(option.logicalDevice, &allocInfo, nullptr, &option.bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(option.logicalDevice, option.buffer, option.bufferMemory, 0);
}

uint32_t Utils::Vulkan::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice device) {
    VkPhysicalDeviceMemoryProperties memProperties;

    vkGetPhysicalDeviceMemoryProperties(device, &memProperties);
    
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void Utils::Vulkan::copyBuffer(struct CopyBufferOption option)
{
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(option.device, option.commandPool);

    VkBufferCopy copyRegion{};
    copyRegion.size = option.size;
    vkCmdCopyBuffer(commandBuffer, option.srcBuffer, option.dstBuffer, 1, &copyRegion);

    endSingleTimeCommands(commandBuffer, option.graphicsQueue, option.device, option.commandPool);
}

VkCommandBuffer Utils::Vulkan::beginSingleTimeCommands(VkDevice device, VkCommandPool commandPool)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void Utils::Vulkan::endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue graphicsQueue, VkDevice device, VkCommandPool commandPool)
{
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);

    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}
