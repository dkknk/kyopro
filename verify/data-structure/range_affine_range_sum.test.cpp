#line 1 "verify/data-structure/range_affine_range_sum.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include<bits/stdc++.h>
#line 3 "lib/graph/graph.hpp"
using namespace std;

template <typename T>
struct Edge{
    int src,to;
    T cost;

    Edge(int to,T cost) : src(-1),to(to),cost(cost){}
    Edge(int src,int to,T cost) : src(src),to(to),cost(cost){}
    Edge &operator = (const int &x){
        to = x;
        return *this;
    }
    operator int() const{return to;}
};

template<class T>
using Edges = vector<Edge<T>>;
template<class T>
using WeightedGraph = vector<Edges<T>>;
using UnWeightedGraph = vector<vector<int>>;
#line 2 "lib/utility.hpp"
namespace detail {
  template <typename Tp, size_t Nb>
  auto make_v(std::vector<size_t>& sizes, Tp const& x) {
    if constexpr (Nb == 1) {
      return std::vector(sizes[0], x);
    } else {
      size_t size = sizes[Nb-1];
      sizes.pop_back();
      return std::vector(size, make_v<Tp, Nb-1>(sizes, x));
    }
  }
}  // detail::

template <typename Tp, size_t Nb>
auto make_v(size_t const(&sizes)[Nb], Tp const& x = Tp()) {
  std::vector<size_t> s(Nb);
  for (size_t i = 0; i < Nb; ++i) s[i] = sizes[Nb-i-1];
  return detail::make_v<Tp, Nb>(s, x);
}
template<class T> bool chmax(T &a, const T &b){if(a<b) {a=b;return 1;}return 0;}
template<class T> bool chmin(T &a, const T &b){if(a>b) {a=b;return 1;}return 0;}
long long gcd(long long a,long long b){return b?gcd(b,a%b):a;}
void yn(bool ok){
    if(ok) cout << "Yes\n";
    else cout << "No\n";
}

#line 5 "lib/math/modint.hpp"

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
#line 4 "lib/data-structure/lazysegtree.hpp"

namespace detail {

inline int bit_ceil(int n) {
    int x = 1;
    while (x < n) x <<= 1;
    return x;
}

inline int countr_zero(unsigned int n) {
    int x = 0;
    while ((n & 1U) == 0) {
        n >>= 1;
        x++;
    }
    return x;
}

}  // namespace detail

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}

    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}

    explicit lazy_segtree(const std::vector<S>& v) : _n((int)v.size()) {
        size = detail::bit_ceil(_n);
        log = detail::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() const {
        return d[1];
    }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1;
            r >>= 1;
        }

        l = l2;
        r = r2;

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)>
    int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }

    template <class G>
    int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while ((l & 1) == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l <<= 1;
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(S)>
    int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }

    template <class G>
    int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (r << 1) + 1;
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) {
        d[k] = op(d[2 * k], d[2 * k + 1]);
    }

    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }

    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
#line 7 "verify/data-structure/range_affine_range_sum.cpp"
#define rep(i,j,n) for(int i=j;i<(int)(n);i++)
#define rrep(i,j,n)  for(int i=j;i>=(int)(n);i--)
#define all(x) (x).begin(),(x).end()
#define pb emplace_back
#define perm(c) sort(all(c)); for(bool c##p=1;c##p;c##p=next_permutation(all(c)))
#define UNIQUE(v) sort(v.begin(),v.end()); v.erase(unique(v.begin(),v.end()),v.end())

using namespace std;
using std::cout;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ll LINF = 1LL << 60LL;
const int IINF = (1 << 30) - 1;

void solve();

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    ll T;
    T = 1;
    /*
       cin >> T;
       */
    while(T--) solve();
}

using mint = modint998244353;
struct S{
    mint val;
    int len;
};
struct F{
    mint b,c;
};
S op(S l,S r){
    return S{l.val+r.val,l.len+r.len};
}
S e(){return S{0,0};}
S mapping(F f,S s){
    return S{s.val*f.b+s.len*f.c,s.len};
}
F composition(F f,F g){
    return F{f.b*g.b,f.b*g.c+f.c};
}
F id(){return F{1,0};}
void solve(){
    int n,q; cin >> n >> q;
    vector<int> a(n);
    rep(i,0,n) cin >> a[i];
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
    rep(i,0,n) seg.set(i,S{a[i],1});
    while(q--){
        int t; cin >> t;
        if(t){
            int l,r; cin >> l >> r;
            cout << seg.prod(l,r).val.val() << "\n";
        }
        else{
            int l,r,b,c; cin >> l >> r >> b >> c;
            seg.apply(l,r,F{mint::raw(b),mint::raw(c)});
        }
    }
}
