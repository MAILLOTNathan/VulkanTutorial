//
//  Version.hpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 06/03/2025.
//

#ifndef _ETIB_VERSION_HPP_
#define _ETIB_VERSION_HPP_

    #include <vulkan/vulkan.h>
    #include <cstdint>

class Version {
    public:
        Version(unsigned int major, unsigned int minor, unsigned int patch);
        ~Version();
    
        uint32_t to_uint32_t();

        unsigned int _major;
        unsigned int _minor;
        unsigned int _patch;
};

#endif
