#include <vector>

template<size_t maxN>
struct Sieve {
    std::vector<int> is_prime;
    std::vector<int> prime;
    std::vector<int> minfac;
    Sieve() : is_prime(maxN, 1), prime(), minfac(maxN, -1) {
        is_prime[0] = is_prime[1] = 0;
        std::iota(minfac.begin(), minfac.end(), 0);
        for (size_t i = 4; i <= maxN; i+=2) {
            is_prime[i] = 0;
            minfac[i] = 2;
        }
        for (size_t i = 3; i*i <= maxN; i+=2) {
            if (!is_prime[i]) continue;
            minfac[i] = i;
            for (size_t j = i*i; j <= maxN; j+=2*i) {
                is_prime[j] = 0;
                if (minfac[j] > i) minfac[j] = i;
            }
        }
        for (size_t i = 2; i <= maxN; i++) {
            if (is_prime[i]) prime.emplace_back(i);
        }
    }
    std::vector<std::pair<int,int>> factorize(int N) {
        std::vector<std::pair<int,int>> res;
        while (N != 1) {
            int bs = minfac[N], exp = 0;
            while (minfac[N] == bs) {
                N /= bs;
                exp++;
            }
            res.emplace_back(bs, exp);
        }
        return res;
    }
    std::vector<int> divisors(int N) {
        std::vector<int> res{1};
        for (auto [bs, exp] : factorize(N)) {
            int len = res.size();
            for (int i = 0; i < len; i++) {
                int x = 1;
                for (int j = 0; j < exp; j++) {
                    x *= bs;
                    res.emplace_back(res[i] * x);
                }
            }
        }
        return res;
    }
};

/**
 * @brief Sieve of Eratosthenes
 */