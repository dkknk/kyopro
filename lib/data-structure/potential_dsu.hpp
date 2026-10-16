// https://github.com/dkknk/kyopro/blob/main/lib/data-structure/potential_dsu.hpp
#pragma once
#include <vector>
#include <cassert>
#include <algorithm>

template <typename T>
struct potential_dsu {
    public:
    potential_dsu() : _n(0) {}
    explicit potential_dsu(int n) : _n(n), parent_or_size(n, -1),height(n,0) {}

    int merge(int a, int b,T h) { //a-b=h
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]){
            std::swap(x, y);
            std::swap(a, b);
            h *= -1;
        }
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        height[y] = -h+height[a]-height[b];
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        return _leader(a).first;
    }

    T dist(int a,int b){
        assert(same(a,b));
        (void)leader(a);
        (void)leader(b);
        return height[a]-height[b];
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
    std::vector<T> height;

    pair<int,T> _leader(int a) {
        if (parent_or_size[a] < 0) return {a,height[a]};
        auto [siz,h] = _leader(parent_or_size[a]);
        return {parent_or_size[a] = siz,height[a] += h};
    }
};