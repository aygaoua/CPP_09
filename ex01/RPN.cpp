#include "RPN.hpp"

void rpn(char *av) {
    std::stack<int> container;
    int i = 0;

    while (av[i])
    {
        if (av[i] == ' ')
        {
            i++;
        }
        if (isdigit(av[i]))
        {
            int n =  av[i];
            container.push(n - 48);
        }
        else if ((av[i] == '+' \
                        || av[i] == '-' \
                        || av[i] == '*' \
                        || av[i] == '/') \
                    && container.size() >= 2)
        {
            int a = container.top();
            container.pop();
            int b = container.top();
            container.pop();
            switch (av[i])
            {
                case '+':
                    container.push(a + b);
                    break;
                case '-':
                    container.push(b - a);
                    break;
                case '*':
                    container.push(a * b);
                    break;
                case '/':
                {
                    if (a == 0)
                    {
                        std::cerr << "Error: deviding by zero !!" << std::endl;
                        exit(0);
                    }
                    container.push(b / a);
                    break;
                }
            }
        }
        else
        {
            std::cerr << "Error" << std::endl;
            exit (1);
        }
        i++;
    }
    if (container.size() != 1)
        std::cerr << "Error !" << std::endl;
    else
        std::cout << container.top() << std::endl;
}
