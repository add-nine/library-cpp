#include <vector>
#include <numeric>
#include <algorithm>

class UnionFind {
    std::vector<int> parent, link;
    int num;
public:
    UnionFind(int N) : num(N), parent(N, -1), link(N) {
        std::iota(link.begin(), link.end(), 0);
    }
    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }
        if (parent[u] > parent[v]) std::swap(u, v);
        std::swap(link[u], link[v]);
        parent[u] += parent[v];
        parent[v] = u;
        return true;
    }
    bool same(const int u, const int v) {
        return find(u) == find(v);
    }
    int size(const int x) {
        return -parent[find(x)];
    }
    std::vector<int> group(int x) {
        std::vector<int> member{x};
        for (int i = x; link[i] != x; i = link[i]) {
            member.emplace_back(link[i]);
        }
        return member;
    }
    std::vector<std::vector<int>> all() {
        std::vector<std::vector<int>> groups(num);
        for (int i = 0; i < num; i++) {
            groups[find(i)].emplace_back(i);
        }
        groups.erase(std::remove_if(groups.begin(), groups.end(), [](auto v) {
            return v.empty();
        }), groups.end());
        return groups;
    }
};

/**
 * @brief Union Find / Disjoint Set Union : (union by size) + (path compression)
 */