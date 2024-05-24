#include "../include/tools.hpp"

void print_and_exit(const std::string& message) {
    std::cerr << "///// ERREUR /////" << std::endl;
    std::cerr << message << std::endl;
    std::cerr << "//////////////////" << std::endl;
    std::exit(EXIT_FAILURE);
}
