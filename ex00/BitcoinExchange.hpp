#include <map>
#include <stdexcept>
#include <fstream>

#define FILENAME "data.csv"
#define DB_ERR "Error: MAIN DB: "

class BitcoinExchange
{
    private:
        std::map<std::string, double> data;
    public:
        BitcoinExchange() {};
        BitcoinExchange(BitcoinExchange const &) {};
        BitcoinExchange operator=(BitcoinExchange &) {};
        ~BitcoinExchange() {};

        void    loadInternalDb();
        void    parseMainDbLine(std::string const &line);
        void    insertLineintoMap(std::string const &line, std::string const &delim, std::map<std::string, double> map);

};
