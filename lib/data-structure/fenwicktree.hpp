#pragma once
// https://github.com/dkknk/kyopro/blob/main/lib/data-structure/fenwicktree.hpp
#include <vector>
#include <cassert>

template <class T>
struct fenwick_tree {
  public:
    fenwick_tree() : _n(0) {}
    explicit fenwick_tree(int n) : _n(n), data(n, T{}) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += x;
            p += p & -p;
        }
    }

    // [0, r)
    T sum(int r) const {
        assert(0 <= r && r <= _n);
        T s = T{};
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }

    // [l, r)
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

    int size() const {
        return _n;
    }

  private:
    int _n;
    std::vector<T> data;
};