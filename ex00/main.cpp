#include <iostream>
#include "BitcoinExchange.hpp"
int main(int ac, const char **av) {

    if (ac != 2 || (ac > 1 && !*av[1])){
      std::cout << "Usage: ./btc DBFilename" << std::endl;
      return 1;
    }

	BitcoinExchange session;

    try {
      session.loadInternalDb();
    }
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
	}
}