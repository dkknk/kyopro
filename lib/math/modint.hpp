#pragma once
// https://github.com/dkknk/kyopro/blob/main/lib/math/modint.hpp
#include <cassert>
#include <cstdint>
#include <iostream>

template <int m>
struct static_modint {
    static_assert(1 <= m);

  public:
    using mint = static_modint;

    static constexpr int mod() { return m; }

    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    static_modint() : _v(0) {}

    template <class T>
    static_modint(T v) {
        long long x = (long long)(v % (long long)(m));
        if (x < 0) x += m;
        _v = (unsigned int)(x);
    }

    unsigned int val() const { return _v; }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= m) _v -= m;
        return *this;
    }

    mint& operator-=(const mint& rhs) {
        if (_v < rhs._v) _v += m;
        _v -= rhs._v;
        return *this;
    }

    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % m);
        return *this;
    }

    mint& operator/=(const mint& rhs) {
        return *this *= rhs.inv();
    }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const {
        assert(n >= 0);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }

    mint inv() const {
        return pow(m - 2);
    }

    friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }

    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }

    friend std::ostream& operator<<(std::ostream& os, const mint& x) {
        return os << x.val();
    }

    friend std::istream& operator>>(std::istream& is, mint& x) {
        long long v;
        is >> v;
        x = mint(v);
        return is;
    }

  private:
    unsigned int _v;
};

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;