#include "BitcoinExchange.hpp"
#include <sstream>

void    BitcoinExchange::loadInternalDb(){
    std::ifstream dataFile(FILENAME);

    if ( dataFile.fail() ){
        std::string msg = DB_ERR"file failed to open, expected file was ";
        throw( std::runtime_error(msg + FILENAME) );
    }

    std::string singleLine;
    
    
    if ( !std::getline(dataFile, singleLine) || singleLine != "date,exchange_rate" ){
        throw std::runtime_error(DB_ERR"improper file start format, it must begin with {{date,exchange_rate}}");
    }

    while ( std::getline(dataFile, singleLine) ) {
        parseMainDbLine(singleLine);
        insertLineintoMap(singleLine, ",", this->data);
    }
}

void    BitcoinExchange::parseMainDbLine(std::string const & line){
    if (line.empty()){
        throw std::runtime_error(DB_ERR"found and empty line");
    }
    if (line.find_first_not_of("1234567890-,.") != std::string::npos){ // ineficient but works to prevent headaches
        throw std::runtime_error(DB_ERR"invalid character found");
    }

    //',' should be found
    size_t pos = 0;
    if ((pos = line.find(',')) != std::string::npos){
        throw std::runtime_error (DB_ERR"invalid line format, it must have a ',' delimiter");
    }
    std::string date = line.substr(0, pos);

    // parsing the date
    // split by year-month-day
    if ()
    double year;
    double month;
    double day;

    size_t start = 0;
    size_t delim = find('-');
    std::istringstream(date.substr(start, delim)) >> year;
    std::istringstream(date.substr(0, date.find('-'))) >> year;
}
