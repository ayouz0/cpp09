#include <stack>
#include <list>
#include <string>
#include <iostream>


class RPN
{
    private:
        std::stack<int, std::list<int> > stack;
        std::list<std::string> tokens;
        void    splitToTokens(std::string &input);
        bool isOperand(const std::string& token);
    public: 
        RPN() {};
        RPN(RPN const &){};
        RPN &operator=(RPN const &){
            return *this;
        };
        ~RPN(){};

        void    parseTokens(std::string input);
        int    postfixNotationCalculation();

};
