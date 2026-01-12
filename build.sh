#!/bin/bash

# Fetching submodules
echo "<--- Fetching submodules --->"
git submodule update --init --recursive

# Build the project
echo "<--- Building the Vulkan Tutorial project --->"
mkdir -p build
cd build
cmake ..
cmake --build .