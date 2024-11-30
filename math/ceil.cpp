#include <cassert>

template<class T>
constexpr T ceil(const T &x, const T &y) {
    assert(y != 0);
    return x / y + (x % y > 0);
}