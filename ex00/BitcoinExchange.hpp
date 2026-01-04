#include <map>
#include <stdexcept>
#include <fstream>

#define FILENAME "data.csv"
#define DB_ERR "Error: MAIN DB: "

class BitcoinExchange
{
    public:
        BitcoinExchange() {};
        BitcoinExchange(BitcoinExchange const &) {};
        BitcoinExchange operator=(BitcoinExchange &) {
            return *this;
        };
        ~BitcoinExchange() {};
        std::map<std::string, double> data;
        std::string currentDate;
        float       currentQuantity;
        void    loadInternalDb();
        void    parse(std::string const & line, std::string const & delimiter);
        void    insertLineintoMap(std::string const & line, std::string const & delimiter);

};
