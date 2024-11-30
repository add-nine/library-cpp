#include <set>
#include <cassert>
#include <iostream>
#include <iterator>

template<class T>
class topN_set {
    int N;
    T sum;
    std::multiset<T> ms1, ms2;
public:
    explicit topN_set(int size) : N(size), sum(0) {}
    void insert(const T x) {
        if (N == 0) {
            ms2.insert(x);
            return;
        }
        if (static_cast<T>(ms1.size()) < N) {
            ms1.insert(x);
            sum += x;
        } else if (ms2.empty()) {
            auto it = std::prev(ms1.end());
            if (x < *it) {
                sum += x - *it;
                ms2.insert(*it);
                ms1.erase(it);
                ms1.insert(x);
            } else {
                ms2.insert(x);
            }
        } else {
            auto it = std::prev(ms1.end());
            T y = *ms2.begin();
            if (x <= y && x < *it) {
                sum += x - *it;
                ms2.insert(*it);
                ms1.erase(it);
                ms1.insert(x);
            }
            else {
                ms2.insert(x);
            }
        }
    }
    bool erase(const T x) {
        if (N == 0) {
            auto it = ms2.find(x);
            if (it != ms2.end()) {
                ms2.erase(it);
                return true;
            }
            return false;
        }
        auto it2 = ms2.find(x);
        if (it2 != ms2.end()) {
            ms2.erase(it2);
            return true;
        }
        auto it1 = ms1.find(x);
        if (it1 != ms1.end()) {
            sum -= *it1;
            ms1.erase(it1);
            if (!ms2.empty()) {
                sum += *ms2.begin();
                ms1.insert(*ms2.begin());
                ms2.erase(ms2.begin());
            }
            return true;
        }
        return false;
    }
    bool full() const {return static_cast<int>(ms1.size()) == N;}
    T top() const {
        assert(!ms1.empty());
        return *ms1.begin();
    }
    T bottom() const {
        assert(!ms1.empty());
        return *ms1.rbegin();
    }
    T sum_all() const {return sum;}
    std::multiset<T> get() const {
        return std::multiset<T>(ms1.begin(), ms1.end());
    }
    void dump() const {
        std::cout << "Top N elements: [";
        for (auto x : ms1) std::cout << x << ", ";
        std::cout << "...]\n";
    }
};

/**
 * @brief  Maintains the top N smallest elements
 */