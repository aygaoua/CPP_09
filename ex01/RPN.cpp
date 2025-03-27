#include "RPN.hpp"

void rpn(char *av) {
    std::stack<long> container;
    int i = 0;

    while (av[i])
    {
        if (av[i] == ' ')
            i++;
        if (isdigit(av[i]) && (i == 0 || (av[i - 1] == ' '))) {
            int n =  av[i];
            container.push(n - 48);
        }
        else if ((av[i] == '+' \
                        || av[i] == '-' \
                        || av[i] == '*' \
                        || av[i] == '/') \
                    && container.size() >= 2 && (i == 0 || (av[i - 1] == ' '))) {
            long a = container.top();
            container.pop();
            long b = container.top();
            container.pop();
            switch (av[i]) {
                case '+': {
                    if (a * b > std::numeric_limits<int>::max() || a * b < std::numeric_limits<int>::min()) {
                        std::cerr << "Error: out of range of integer !!" << std::endl;
                        exit(0);
                    }
                    container.push(a + b);
                    break;
                }
                case '-': {
                    if (a * b > std::numeric_limits<int>::max() || a * b < std::numeric_limits<int>::min()) {
                        std::cerr << "Error: out of range of integer !!" << std::endl;
                        exit(0);
                    }
                    container.push(b - a);
                    break;
                }
                case '*': {
                    if (a * b > std::numeric_limits<int>::max() || a * b < std::numeric_limits<int>::min()) {
                        std::cerr << "Error: out of range of integer !!" << std::endl;
                        exit(0);
                    }
                    container.push(a * b);
                    break;
                }
                case '/': {
                    if (a == 0) {
                        std::cerr << "Error: deviding by zero !!" << std::endl;
                        exit(0);
                    }
                    if (a * b > std::numeric_limits<int>::max() || a * b < std::numeric_limits<int>::min()) {
                        std::cerr << "Error: out of range of integer !!" << std::endl;
                        exit(0);
                    }
                    container.push(b / a);
                    break;
                }
            }
        }
        else {
            std::cerr << "Error" << std::endl;
            exit (1);
        }
        i++;
    }
    if (container.size() != 1)
        std::cerr << "Error" << std::endl;
    else
        std::cout << container.top() << std::endl;
}
