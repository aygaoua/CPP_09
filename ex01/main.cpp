#include "RPN.hpp"

int main(int ac, char **av) {
    if (ac != 2)
    {
        std::cerr << "Error: number of args is wrong" << std::endl;
    }
    try {
        rpn(av[1]);
    }
    catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return (0);
}