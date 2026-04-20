#line 1 "verify/data-structure/staticrmq.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
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
#line 4 "lib/data-structure/segtree.hpp"

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
} 

template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
  public:
    segtree() : segtree(0) {}

    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}

    explicit segtree(const std::vector<S>& v) : _n((int)v.size()) {
        size = detail::bit_ceil(_n);
        log = detail::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

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

    template <bool (*f)(S)>
    int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }

    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while ((l & 1) == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l <<= 1;
                    if (f(op(sm, d[l]))) {
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

    template <bool (*f)(S)>
    int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }

    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (r << 1) + 1;
                    if (f(op(d[r], sm))) {
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

    void update(int k) {
        d[k] = op(d[2 * k], d[2 * k + 1]);
    }
};
#line 6 "verify/data-structure/staticrmq.cpp"
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

ll op(ll a,ll b){return min(a,b);}
ll e(){return LINF;}
void solve(){
    ll n,q; cin >> n >> q;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    segtree<ll,op,e> seg(a);
    while(q--){
        ll l,r; cin >> l >> r;
        cout << seg.prod(l,r) << "\n";
    }
}

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
