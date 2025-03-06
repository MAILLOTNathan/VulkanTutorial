#include "App.hpp"

int main(int ac, char **av, char **env) {
    App *app = new App("Vulkan Tutorial", Version(1, 0, 0), "ETIB", Version(1, 0, 0));

    try {
        app->run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
