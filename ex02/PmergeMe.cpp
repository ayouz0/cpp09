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
    this->sortVector(_vector);
    std::cout << "Vector Comparisons: " << Stats::comparisons << std::endl;

    // Stats::reset();
    // std::cout << "Sorting Deque..." << std::endl;
    // this->sortDeque();
    // std::cout << "Deque Comparisons: " << Stats::comparisons << std::endl;
}

void PmergeMe::sortVector(std::vector<Tracked<unsigned int> > &vec) {
    if (vec.size() <= 1) return;

    bool hasStraggler = false;
    Tracked<unsigned int> straggler(0);
    if (vec.size() % 2 != 0) {
        hasStraggler = true;
        straggler = vec.back();
        vec.pop_back();
    }

    std::vector<std::pair<Tracked<unsigned int>, Tracked<unsigned int> > > pairs;
    for (size_t i = 0; i < vec.size(); i += 2) {
        if (vec[i] > vec[i + 1]) {
            pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
        } else {
            pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
        }
    }

    std::vector<Tracked<unsigned int> > mainChain;
    for (size_t i = 0; i < pairs.size(); i++) {
        mainChain.push_back(pairs[i].first);
    }

    sortVector(mainChain);
    std::vector<Tracked<unsigned int> > pend;
    for (size_t i = 0; i < mainChain.size(); i++) {
        for (size_t j = 0; j < pairs.size(); j++) {
            if (pairs[j].first == mainChain[i]) {
                pend.push_back(pairs[j].second);
                pairs.erase(pairs.begin() + j); 
                break;
            }
        }
    }
    mainChain.insert(mainChain.begin(), pend[0]);

    size_t insertionCount = 1;
    
    for(size_t i = 1; i < mainChain.size(); i++) {

        Tracked<unsigned int> toInsert = pend[i];

        
    }
}