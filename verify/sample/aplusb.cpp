#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include<bits/stdc++.h>
#include<atcoder/all>
#include "lib/graph/graph.hpp"
#include "lib/utility.hpp"
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

    ll T=1;
    while(T--) solve();
}