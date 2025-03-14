//
//  QueueFamily.cpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 14/03/2025.
//

#include "QueueFamilyIndices.hpp"

QueueFamilyIndices::QueueFamilyIndices(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            _graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if (presentSupport) {
            _presentFamily = i;
        }

        if (this->isComplete()) {
            break;
        }

        i++;
    }
}

QueueFamilyIndices::~QueueFamilyIndices()
{
}

bool QueueFamilyIndices::isComplete()
{
    return _graphicsFamily.has_value() && _presentFamily.has_value();
}

std::optional<uint32_t> QueueFamilyIndices::getGraphicsFamily() const
{
    return _graphicsFamily;
}

std::optional<uint32_t> QueueFamilyIndices::getPresentFamily() const
{
    return _presentFamily;
}

uint32_t QueueFamilyIndices::getGraphicsFamilyValue() const
{
    return _graphicsFamily.value();
}

uint32_t QueueFamilyIndices::getPresentFamilyValue() const
{
    return _presentFamily.value();
}
