#include "PmergeMe.hpp"
#include <sstream>
#include <iostream>
#include <set>
#include <stdexcept>

// Initialize static member
size_t Stats::comparisons = 0;

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int ac, const char **av) {
    std::set<unsigned int> duplicates;

    for (int i = 1; i < ac; i++) {
        unsigned int value;
        std::string stringVal(av[i]);

        if (stringVal.find_first_not_of("0123456789") != std::string::npos) {
            throw std::runtime_error("Invalid token found: " + stringVal);
        }

        std::stringstream strStream(stringVal);
        strStream >> value;

        if (strStream.fail()) {
            throw std::runtime_error("value overflows or has an invalid lenght: " + stringVal);
        }
        if (duplicates.find(value) != duplicates.end()) {
            throw std::runtime_error("duplicate element found: " + stringVal);
        }
        duplicates.insert(value);

        _vector.push_back(Tracked<unsigned int>(value));
        _deque.push_back(Tracked<unsigned int>(value));
    }
}

void PmergeMe::start(int ac, const char **av) {
    if (ac < 2){
        std::cerr << "usage: ./PmergeMe <unsigned numbers>" << std::endl;
        return;
    }
    try {
        parseInput(ac, av);
    }
    catch(std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return;
    }

    Stats::reset();
    std::cout << "Sorting Vector..." << std::endl;
    this->sortVector();
    std::cout << "Vector Comparisons: " << Stats::comparisons << std::endl;

    // Stats::reset();
    // std::cout << "Sorting Deque..." << std::endl;
    // this->sortDeque();
    // std::cout << "Deque Comparisons: " << Stats::comparisons << std::endl;
}

void    PmergeMe::sortVector(){

    bool hasStraggler = false;
    Tracked <unsigned int> straggler(_vector.back());
    if (_vector.size() % 2 != 0){
        // we have a straggler
        hasStraggler = true;
        _vector.pop_back();
    }

    std::vector < std::pair< Tracked<unsigned int>, Tracked<unsigned int> > > pairs (_vector.size() / 2);
    for (size_t pairsIter = 0; pairsIter < pairs.size() ; pairsIter++){

        size_t vecIter = pairsIter * 2;

        pairs[pairsIter].first = _vector[vecIter];
        pairs[pairsIter].second = _vector[vecIter + 1];
    }

    std::vector< Tracked<unsigned int> > winners(_vector.size() / 2);
    std::vector< Tracked<unsigned int> > loosers((_vector.size() / 2));

    for (size_t i = 0; i < winners.size(); i++)
    {
        if (pairs[i].first < pairs[i].second){
            winners[i] = pairs[i].second;
            pairs[i].second = pairs[i].first;
        }
        else{

            winners[i] = pairs[i].first;
        }

        

        loosers[i] =  pairs[i].second;
    }




    
    // std::cout << "winners\n";
    // for (size_t i = 0; i < winners.size(); i++)
    // {
    //     std::cout << winners[i] << std::endl;
    // }
    
    // std::cout << "loosers\n";
    // for (size_t i = 0; i < loosers.size(); i++)
    // {
    //     std::cout << loosers[i] << std::endl;
    // }
    std:: cout << "straggler\n" << straggler << std::endl;

}
