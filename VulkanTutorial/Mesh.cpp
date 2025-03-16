//
//  Mesh.cpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 14/03/2025.
//

#include "Mesh.hpp"

Mesh::Mesh(VkDevice logicalDevice, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<Vertex> vertices)
{
    if (vertices.empty())
        return;
    VkDeviceSize bufferSize = sizeof(_vertices[0]) * _vertices.size();
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    
    Utils::Vulkan::createBuffer({
        .size = bufferSize,
        .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        .properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        .buffer = stagingBuffer,
        .bufferMemory = stagingBufferMemory,
        .logicalDevice = logicalDevice,
        .physicalDevice = physicalDevice,
    });

    void* data;
    vkMapMemory(logicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, _vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(logicalDevice, stagingBufferMemory);

    Utils::Vulkan::createBuffer({
        .size = bufferSize,
        .usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        .properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        .buffer = _vertexBuffer,
        .bufferMemory = _vertexBufferMemory,
        .logicalDevice = logicalDevice,
        .physicalDevice = physicalDevice
    });
    Utils::Vulkan::copyBuffer({
        .size = bufferSize,
        .device = logicalDevice,
        .commandPool = commandPool,
        .srcBuffer = stagingBuffer,
        .dstBuffer = _vertexBuffer,
        .graphicsQueue = graphicsQueue
    });
    
    vkDestroyBuffer(logicalDevice, stagingBuffer, nullptr);
    vkFreeMemory(logicalDevice, stagingBufferMemory, nullptr);
}
