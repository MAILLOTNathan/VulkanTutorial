#  compile.sh
#  VulkanTutorial
#
#  Created by Nathan Maillot on 06/03/2025.
#

export PATH_TO_GLSLC="/usr/local/bin/glslc"

$PATH_TO_GLSLC shader.vert -o vert.spv
$PATH_TO_GLSLC shader.frag -o frag.spv
