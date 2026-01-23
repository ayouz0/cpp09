#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <ctime>
#include <iomanip>

class PmergeMe {
    public:
        PmergeMe();
        PmergeMe(PmergeMe const &);
        PmergeMe &operator=(PmergeMe &);
        ~PmergeMe();

        void start(int ac, const char **av);

    private:
        std::vector< unsigned int > _vector;
        std::deque< unsigned int >  _deque;

        void parseInput(int ac, const char **av);

        void sortVector(std::vector < unsigned int > &vec);
        void sortDeque(std::deque < unsigned int > &dikio);
};

#endif