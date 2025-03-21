//
//  Utils.hpp
//  VulkanTutorial
//
//  Created by Nathan Maillot on 06/03/2025.
//

#ifndef _ETIB_UTILS_HPP_
#define _ETIB_UTILS_HPP_

#include <fstream>

class Utils {
    public:
        static std::vector<char> readFile(const std::string& filename) {
            std::ifstream file(filename, std::ios::ate | std::ios::binary);

            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }
            
            size_t fileSize = (size_t) file.tellg();
            std::vector<char> buffer(fileSize);
            file.seekg(0);
            file.read(buffer.data(), fileSize);
            file.close();

            return buffer;
        }
};

#endif
