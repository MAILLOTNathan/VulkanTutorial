//
//  QueueFamilyIndices.hpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 14/03/2025.
//

#ifndef ETIB_QUEUE_FAMILY
    #define ETIB_QUEUE_FAMILY

#include <vulkan/vulkan.h>

#include <optional>
#include <memory>
#include <vector>

class QueueFamilyIndices {
    public:
        QueueFamilyIndices(VkPhysicalDevice device, VkSurfaceKHR surface);
        ~QueueFamilyIndices();

        bool isComplete();
    
        std::optional<uint32_t> getGraphicsFamily() const;
        std::optional<uint32_t> getPresentFamily() const;
        uint32_t getGraphicsFamilyValue() const;
        uint32_t getPresentFamilyValue() const;


    protected:
        std::optional<uint32_t> _graphicsFamily;
        std::optional<uint32_t> _presentFamily;
};

#endif
