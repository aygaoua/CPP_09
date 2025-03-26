#include "PmergeMe.hpp"

int main (int ac, char **av) {
    if (ac < 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    try {
        merge_insert_global(ac, av);
    }
    catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Error: catch in the main" << std::endl;
    }
    return (0);
}