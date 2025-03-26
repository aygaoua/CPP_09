#include "BitcoinExchange.hpp"

int main(int ac, char **av) {

	if (ac != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	try {
		btc(av);
	}
	catch(std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return (0);
}