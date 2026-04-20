#line 1 "verify/sample/aplusb.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include<bits/stdc++.h>
#include<atcoder/all>
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
long long gcd(long long a,long long b){return b?gcd(b,a%b):a;}
void yn(bool ok){
    if(ok) cout << "Yes\n";
    else cout << "No\n";
}
#line 6 "verify/sample/aplusb.cpp"
#define rep(i,j,n) for(ll i=j;i<(ll)(n);i++)
#define rrep(i,j,n)  for(ll i=j;i>=n;i--)
#define all(x) (x).begin(),(x).end()
#define m0(x) memset(x,0,sizeof(x))
#define pb emplace_back
#define mp make_pair
#define perm(c) sort(all(c)); for(bool c##p=1;c##p;c##p=next_permutation(all(c)))
#define UNIQUE(v) sort(v.begin(),v.end()); v.erase(unique(v.begin(),v.end()),v.end())

using namespace std;
using namespace atcoder;
using std::cout;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<class T> bool chmax(T &a, const T &b){if(a<b) {a=b;return 1;}return 0;}
template<class T> bool chmin(T &a, const T &b){if(a>b) {a=b;return 1;}return 0;}
const ll LINF = 1LL << 60LL;
const int IINF = (1 << 30) - 1;

void solve(){
    ll a,b; cin >> a >> b;
    cout << a+b << "\n";
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
