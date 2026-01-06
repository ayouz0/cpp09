#include "BitcoinExchange.hpp"
#include <sstream>
#include <cstdlib>
#include <limits>

void    BitcoinExchange::loadInternalDb(){
    std::ifstream dataFile(FILENAME);

    if ( dataFile.fail() ){
        std::string msg = "file failed to open, expected file was ";
        throw( std::runtime_error(msg + FILENAME) );
    }

    std::string singleLine;
    
    if ( !std::getline(dataFile, singleLine) || singleLine != "date,exchange_rate" ){
        throw std::runtime_error(DB_ERR"improper file start format, it must begin with {{date,exchange_rate}}");
    }

    while ( std::getline(dataFile, singleLine) ) {
        parse(singleLine, ",");
        insertLineintoMap(singleLine, ",");
    }
}

void    BitcoinExchange::parse(std::string const & line, std::string const & delimiter){
    if (line.empty()){
        throw std::runtime_error("found and empty line");
    }
    if (delimiter == " | "){
        if (line.find_first_not_of("1234567890-. |") != std::string::npos){
            throw std::runtime_error("invalid character found in input line");
        }
    }
    else if (delimiter == ","){
        if (line.find_first_not_of("1234567890-.,") != std::string::npos){
            throw std::runtime_error("invalid character found in database line");
        }
    }

    size_t pos = line.find(delimiter);
    if ( pos == std::string::npos ){
        throw std::runtime_error("missing delimiter in line");
    }
    std::string date = line.substr(0, pos);

    // parsing the date
    if ( date.length() != 10 || date[4] != '-' || date[7] != '-' ){
        throw std::runtime_error("invalid date format found in line");
    }
    std::istringstream   dateStream(date);
    std::string          segment;
    int                 dateParts[3];
    int                 i = 0;
    
    while (std::getline(dateStream, segment, '-')) {
        dateParts[i] = std::atoi(segment.c_str());
        i++;
    }
    if ( dateParts[1] < 1 || dateParts[1] > 12 ){
        throw std::runtime_error("invalid month found in date");
    }
    int daysInMonth = 31; 

    if (dateParts[1] == 4 || dateParts[1] == 6 || dateParts[1] == 9 || dateParts[1] == 11) {
        daysInMonth = 30;
    }
    else if (dateParts[1] == 2) {
        bool isLeap = (dateParts[0] % 4 == 0 && (dateParts[0] % 100 != 0 || dateParts[0] % 400 == 0));
        daysInMonth = isLeap ? 29 : 28;
    }
    if (dateParts[2] < 1 || dateParts[2] > daysInMonth) {
         throw std::runtime_error("invalid day found in date");
    }
    std::string rateStr = line.substr(pos + delimiter.length()); 
    double rate = std::atof(rateStr.c_str());
    if ( rate < 0.0 ){
        throw std::runtime_error("negative exchange rate found");
    }

    if (delimiter == " | " && rate > 1000.0){
        throw std::runtime_error("too large quantity found in line");
    }
    if (rate > std::numeric_limits<double>::max()){
        throw std::runtime_error("exchange rate too large in line");
    }
    if (delimiter == " | "){
        this->currentDate = date;
        this->currentQuantity = rate;
    }
}

void    BitcoinExchange::insertLineintoMap(std::string const & line, std::string const & delimiter){
    size_t pos = 0;
    std::string token;
    std::string lineCopy = line;
    
    // get date
    pos = lineCopy.find(delimiter);
    token = lineCopy.substr(0, pos);
    std::string date = token;
    lineCopy.erase(0, pos + delimiter.length());

    // get exchange rate
    token = lineCopy;
    double rate = std::atof(token.c_str());
    this->data[date] = rate;
}
