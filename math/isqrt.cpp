#include <cassert>

template <class T>
T isqrt(T n) {
    assert(n >= 0);
    if (n <= 1) return n;
    T x = n, y = (x + n / x) / 2;
    while (y < x) {
        x = y;
        y = (x + n / x) / 2;
    }
    return x;
}

/**
 * @brief computes integer sqrt
 */