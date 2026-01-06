#include "RPN.hpp"

int main(int ac, const char **av){
    if (ac != 2 || (ac == 2 && !*av[1])){
        std::cout << "Error: wrong usage\n Usage: ./RPN {{inverted polish mathematical expression eg: \"3 2 +\"}}" << std::endl;
        return 1;
    }

    RPN session;

    try {
        session.parseTokens(av[1]);
        int result = session.postfixNotationCalculation();
        std::cout << result << std::endl;
    }
    catch (std::runtime_error &e){
        std::cout << e.what() << std::endl;
        return 1;
    }
}