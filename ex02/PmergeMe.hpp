#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>

struct Stats {
    static size_t comparisons;
    static void reset() { comparisons = 0; }
};

template <typename T>
class Tracked {
    public:
        T value;
        Tracked() : value(0) {}
        Tracked(T v) : value(v) {}

        bool operator<(const Tracked& other) const {
            Stats::comparisons++;
            return value < other.value;
        }
        bool operator>(const Tracked& other) const {
            Stats::comparisons++;
            return value > other.value;
        }
        bool operator==(const Tracked& other) const {
            Stats::comparisons++;
            return value == other.value;
        }
        operator T() const { return value; }
};

class PmergeMe {
    public:
        PmergeMe();
        PmergeMe(PmergeMe const &);
        PmergeMe &operator=(PmergeMe &);
        ~PmergeMe();

        void start(int ac, const char **av);

    private:
        std::vector< Tracked<unsigned int> > _vector;
        std::deque< Tracked<unsigned int> >  _deque;

        void parseInput(int ac, const char **av);

        void sortVector(std::vector < Tracked <unsigned int> > &vec);
        void sortDeque();
};

#endif