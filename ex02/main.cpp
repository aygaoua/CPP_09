#include "PmergeMe.hpp"

int main (int ac, char **av) {
    if (ac < 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    merge_insert(ac, av);
    return (0);
}