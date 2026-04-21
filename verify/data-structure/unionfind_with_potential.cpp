#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"
#include<bits/stdc++.h>
#include "lib/graph/graph.hpp"
#include "lib/utility.hpp"
#include "lib/data-structure/potential_dsu.hpp"
#include "lib/math/modint.hpp"
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

using mint = modint998244353;
void solve(){
    ll n,q; cin >> n >> q;
    potential_dsu<mint> d(n);
    while(q--){
        ll t,u,v; cin >> t >> u >> v;
        if(t){
            if(d.same(u,v)) cout << d.dist(u,v) << "\n";
            else cout << "-1\n";
        }
        else{
            mint x; cin >> x;
            if(d.same(u,v))
                cout << (d.dist(u,v) == x) << "\n";
            else{
                d.merge(u,v,x);
                cout << "1\n";
            }
        }
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
