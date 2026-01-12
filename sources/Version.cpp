//
//  Version.cpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 06/03/2025.
//

#include "Version.hpp"

Version::Version(unsigned int major, unsigned int minor, unsigned int patch)
{
    this->_major = major;
    this->_minor = minor;
    this->_patch = patch;
}

Version::~Version()
{

}

uint32_t Version::to_uint32_t()
{
    return VK_MAKE_VERSION(_major, _minor, _patch);
}
