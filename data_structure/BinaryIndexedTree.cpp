#include <vector>
#include <cassert>

template<class T>
class BinaryIndexedTree {
    int N;
    std::vector<T> BIT;
    struct Operation {
        static T op(const T x, const T y) {return x + y;}
        static T inv(const T x, const T y) {return x - y;}
        static T id() {return T();}
    };
public:
    explicit BinaryIndexedTree(const int size) : N(size), BIT(size, Operation::id()) {}
    void add(int i, const T x) {
        assert(0 <= i && i < N);
        for (++i; i <= N; i += i & -i) {
            BIT[i-1] = Operation::op(BIT[i-1], x);
        }
    }
    T sum(int i) {
        assert(0 <= i && i <= N);
        T ans = Operation::id();
        for (; i > 0; i -= i & -i) {
            ans = Operation::op(ans, BIT[i-1]);
        }
        return ans;
    }
    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= N);
        return Operation::inv(sum(r), sum(l));
    }
};

/**
 * @brief Binary Indexed Tree 
 */