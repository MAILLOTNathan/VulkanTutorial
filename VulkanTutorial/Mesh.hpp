//
//  Mesh.hpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 14/03/2025.
//

#ifndef ETIB_MESH
    #define ETIB_MESH

    #include <vulkan/vulkan.h>

    #include <vector>

    #include "Vertex.hpp"
    #include "VulkanUtils.hpp"

class Mesh {
    public:
        Mesh(VkDevice logicalDevice, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<Vertex> vertices = {});
        ~Mesh();
    
    protected:
        std::vector<Vertex> _vertices;
        std::vector<uint32_t> _indices;
        VkBuffer _vertexBuffer;
        VkDeviceMemory _vertexBufferMemory;
};

#endif
