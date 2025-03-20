#include "RPN.hpp"

int main(int ac, char **av) {
    if (ac != 2)
    {
        std::cerr << "Error: number of args is wrong" << std::endl;
    }
    rpn(av[1]);
    return (0);
}