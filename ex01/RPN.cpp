#include "RPN.hpp"
#include <stdexcept>
#include <sstream>
#include <cctype>

// void    trim(std::string &inputToTrim){
//     std::string whiteSpaces(" \n\r\t\v");
//     size_t pos = inputToTrim.find_first_not_of(whiteSpaces);
//     inputToTrim.erase(0, pos);
//     pos = inputToTrim.find_last_not_of(whiteSpaces);
//     inputToTrim.erase(pos, inputToTrim.length() - 1);
//     std::cout << "last state of trimmed string :" << inputToTrim;
// }

void    RPN::splitToTokens(std::string &input){
    std::stringstream ss(input);
    std::string word;
    while (ss >> word) {
        if (word.length() != 1){
            throw std::runtime_error("invalid token length: " + word);
        }
        else {
            this->tokens.push_back(word);
        }
    }

}

bool RPN::isOperand(const std::string& token){
    return std::isdigit(*token.c_str());
}


void    RPN::parseTokens(std::string input){

    if (input.find_first_not_of(" +*-/1234567890") != std::string::npos){
        throw std::runtime_error("invalid character found while parsing tokens");
    }

    // trim(input);
    
    splitToTokens(input);
}
int    RPN::postfixNotationCalculation(){
    std::list<std::string>::iterator it = this->tokens.begin();

    if (this->tokens.size() < 3){
        if (this->tokens.size() == 1){
            if (isOperand(*it)){
                return std::atoi((*it).c_str());
            }
            else {
                throw std::runtime_error("an RPN expression cannot start with an operator");
            }
        }
        else if (this->tokens.size() == 2){
            throw std::runtime_error("an RPN expression should have 1, or more than 2 tokens");
        }
    }

    while (it != this->tokens.end()){
        if (isOperand(*it)){
            this->stack.push(std::atoi((*it).c_str()));
        }
        else {
            int first = stack.top();
            stack.pop();
            int last = stack.top();
            stack.pop();
            int resultToPush;
            if (*it == "+"){
                resultToPush = last + first;
            }
            else if (*it == "*"){
                resultToPush = last * first;
            }
            else if (*it == "-"){
                resultToPush = last - first;
            }
            else if (*it == "/"){
                resultToPush = last / first;
            }
            this->stack.push(resultToPush);
        }
        it++;
    }
    if (stack.size() > 1){
        throw std::runtime_error("not enough operators");
    }
    return stack.top();
}
