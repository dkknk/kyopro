#line 1 "verify/data-structure/unionfind.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
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
#line 4 "lib/data-structure/dsu.hpp"

struct dsu {
    public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        return _leader(a);
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

    int _leader(int a) {
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = _leader(parent_or_size[a]);
    }
};
#line 6 "verify/data-structure/unionfind.cpp"
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

void solve(){
    ll n,q; cin >> n >> q;
    dsu d(n);
    while(q--){
        ll t,u,v; cin >> t >> u >> v;
        if(t) cout << d.same(u,v) << "\n";
        else d.merge(u,v);
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
