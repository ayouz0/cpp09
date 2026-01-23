#include "PmergeMe.hpp"
#include <sstream>
#include <iostream>
#include <set>
#include <stdexcept>


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

        _vector.push_back((unsigned int)(value));
        _deque.push_back((unsigned int)(value));
    }
}

#include <sys/time.h>

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
    
    std::cout<< "Before: ";
    if (_vector.size() <= 5){
        for (size_t i = 0; i < _vector.size(); i++){
            std::cout << _vector[i] << ' ';
        }
    }
    else{
        for (size_t i = 0; i < 5; i++){
            std::cout << _vector[i] << ' ';
        }
    }
    std::cout << std::endl;
    {
        std::clock_t startVec = std::clock();
        
        this->sortVector(_vector);
        
        std::clock_t endVec = std::clock();
        double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000;

        std::cout<< "after : ";
        if (_vector.size() <= 5){
            for (size_t i = 0; i < _vector.size(); i++){
                std::cout << _vector[i] << ' ';
            }
        }
        else{
            for (size_t i = 0; i < 5; i++){
                std::cout << _vector[i] << ' ';
            }
        }
        std::cout << std::endl;

        std::cout << "Time to process a range of " << _vector.size() 
                << " elements with std::vector : " 
                << std::fixed << std::setprecision(5) << timeVec << " us" << std::endl;
    }
    {
        std::cout<< "Before: ";
    if (_deque.size() <= 5){
        for (size_t i = 0; i < _deque.size(); i++){
            std::cout << _deque[i] << ' ';
        }
    }
    else{
        for (size_t i = 0; i < 5; i++){
            std::cout << _deque[i] << ' ';
        }
    }
        std::clock_t startDeq = std::clock();
        
        this->sortDeque(_deque);
        
        std::clock_t endDeq = std::clock();
        double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;

        std::cout<< "\nafter : ";
        if (_deque.size() <= 5){
            for (size_t i = 0; i < _deque.size(); i++){
                std::cout << _deque[i] << ' ';
            }
        }
        else{
            for (size_t i = 0; i < 5; i++){
                std::cout << _deque[i] << ' ';
            }
        }
        std::cout << std::endl;

        std::cout << "Time to process a range of " << _deque.size() 
                << " elements with std::deque  : " 
                << std::fixed << std::setprecision(5) << timeDeq << " us" << std::endl;
    }
}

size_t getJacobsthal(size_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return getJacobsthal(n - 1) + 2 * getJacobsthal(n - 2);
}

void PmergeMe::sortVector(std::vector<unsigned int > &vec) {
    if (vec.size() <= 1) return;

    bool hasStraggler = false;
    unsigned int straggler(0);
    if (vec.size() % 2 != 0) {
        hasStraggler = true;
        straggler = vec.back();
        vec.pop_back();
    }

    std::vector<std::pair<unsigned int, unsigned int > > pairs;
    for (size_t i = 0; i < vec.size(); i += 2) {
        if (vec[i] > vec[i + 1]) {
            pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
        } else {
            pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
        }
    }// first is always winner

    std::vector<unsigned int > mainChain;
    for (size_t i = 0; i < pairs.size(); i++) {
        mainChain.push_back(pairs[i].first);
    }

    sortVector(mainChain);
    std::vector<unsigned int > pend;
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
    size_t jacobIndex = 3; 
    size_t prevJacob = 1; 

    while (1) {
        size_t nextJacob = getJacobsthal(jacobIndex);
        size_t rangeEnd = nextJacob;
        if (rangeEnd > pend.size()) {
            rangeEnd = pend.size();
        }

        for (size_t i = rangeEnd; i > prevJacob; i--) {
            unsigned int toInsert = pend[i - 1];
            
            std::vector<unsigned int >::iterator insertPos;
            
            insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), toInsert);
            
            mainChain.insert(insertPos, toInsert);
        }

        if (rangeEnd == pend.size())
            break;

        prevJacob = nextJacob;
        jacobIndex++;
    }
    if (hasStraggler) {
        std::vector<unsigned int >::iterator insertPos;
        insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(insertPos, straggler);
    }

    vec = mainChain;
}

void PmergeMe::sortDeque(std::deque<unsigned int > &deq) {
    if (deq.size() <= 1) return;

    bool hasStraggler = false;
    unsigned int straggler(0);
    if (deq.size() % 2 != 0) {
        hasStraggler = true;
        straggler = deq.back();
        deq.pop_back();
    }

    std::deque<std::pair<unsigned int, unsigned int > > pairs;
    for (size_t i = 0; i < deq.size(); i += 2) {
        if (deq[i] > deq[i + 1]) {
            pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
        } else {
            pairs.push_back(std::make_pair(deq[i + 1], deq[i]));
        }
    }// first is always winner

    std::deque<unsigned int > mainChain;
    for (size_t i = 0; i < pairs.size(); i++) {
        mainChain.push_back(pairs[i].first);
    }

    sortDeque(mainChain);
    std::deque<unsigned int > pend;
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
    size_t jacobIndex = 3; 
    size_t prevJacob = 1; 

    while (1) {
        size_t nextJacob = getJacobsthal(jacobIndex);
        size_t rangeEnd = nextJacob;
        if (rangeEnd > pend.size()) {
            rangeEnd = pend.size();
        }

        for (size_t i = rangeEnd; i > prevJacob; i--) {
            unsigned int toInsert = pend[i - 1];
            
            std::deque<unsigned int >::iterator insertPos;
            
            insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), toInsert);
            
            mainChain.insert(insertPos, toInsert);
        }

        if (rangeEnd == pend.size())
            break;

        prevJacob = nextJacob;
        jacobIndex++;
    }
    if (hasStraggler) {
        std::deque<unsigned int >::iterator insertPos;
        insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(insertPos, straggler);
    }

    deq = mainChain;
}
