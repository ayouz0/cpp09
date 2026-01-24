#include <iostream>
#include "BitcoinExchange.hpp"
#include <iomanip>
int main(int ac, const char **av) {

    if (ac != 2 || (ac > 1 && !*av[1])){
      std::cout << "Usage: ./btc DBFilename" << std::endl;
      return 1;
    }

    BitcoinExchange session;
    std::ifstream inputFile(av[1]);
    std::string singleLine ;
    try {
      session.loadInternalDb();
      std::cout << "Database loaded successfully" << std::endl;
      if ( inputFile.fail() ){
          std::string msg = "file failed to open, expected file was ";
          throw( std::runtime_error(msg + std::string(av[1])) );
      }
      std::getline(inputFile, singleLine);
      if ( singleLine != "date | value" ){
          throw std::runtime_error("improper input file start format, it must begin with {{date | value}}");
      }
    }
    catch (std::runtime_error &e) {
      std::cout << "Error: " << e.what() <<std::endl;
      return 1;
    }
    while (std::getline(inputFile, singleLine)) {
        try {
            session.parse(singleLine, " | ");
            std::map<std::string, double>::iterator it = session.data.lower_bound(session.currentDate);
            if (it == session.data.end() || it->first != session.currentDate) {
                if (it == session.data.begin()) {
                    throw std::runtime_error("date is older than the oldest record in database");
                }
                --it;
            }

            double exchangeRate = it->second;
            double result = session.currentQuantity * exchangeRate;
            std::cout << session.currentDate << " => " << session.currentQuantity << " = " 
                      << std::fixed << std::setprecision(2) << result << std::endl;
        }
        catch (std::exception &e) {
            std::cout <<  "Error: " << e.what() << " => " << singleLine << std::endl;
        }
    }
}

