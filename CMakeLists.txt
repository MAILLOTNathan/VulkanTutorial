cmake_minimum_required(VERSION 3.10)

project(vulkan-tutorial)

# Set global C++ standard and properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(STB_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/stb")

# Set the files directories
set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/headers" "${STB_HEADERS_DIR}")
set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sources")

# Add the headers directories
include_directories(${HEADERS_DIR})

# FetchContent module
include(FetchContent)

# Fetch Vulkan-Headers
FetchContent_Declare(Vulkan-Headers
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
    GIT_TAG v1.4.329
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(Vulkan-Headers)

set(GLM_BUILD_TESTS OFF)
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glm)

# Collect common source files
file(GLOB SOURCES_COMMON "${SOURCES_DIR}/common/*.cpp" "${SOURCES_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES_COMMON})

# Link common dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan-Headers glm)

# Fetch GLFW for window management
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glfw)

# Add Vulkan compile definition
add_compile_definitions(__GLFW__)

# Collect Vulkan-specific source files
file(GLOB_RECURSE GLFW_SOURCES "${SOURCES_DIR}/glfw/*.cpp")

# Create library with Vulkan support
target_sources(${PROJECT_NAME} PRIVATE ${GLFW_SOURCES})

# Link Vulkan dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Configure public interface
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${HEADERS_DIR}>
        $<INSTALL_INTERFACE:include>
)
